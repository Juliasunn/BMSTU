#include "asyncserver.h"

// Handles an HTTP server connection
class session : public std::enable_shared_from_this<session>
{
    beast::tcp_stream stream_;
    beast::flat_buffer buffer_;
    http::request<http::string_body> req_;

public:
    // Take ownership of the stream
    session(tcp::socket&& socket, const std::string &confileName)
        : stream_(std::move(socket))
    {
        ServerConfig sConf = ServerConfig(confileName);
        control.setConf(sConf);

    }

    // Start the asynchronous operation
    void run()
    {
        // We need to be executing within a strand to perform async operations
        // on the I/O objects in this session. Although not strictly necessary
        // for single-threaded contexts, this example code is written to be
        // thread-safe by default.
        net::dispatch(stream_.get_executor(),
                      beast::bind_front_handler(
                          &session::do_read,
                          shared_from_this()));
    }

    void do_read()
    {
        req_ = {};        
        stream_.expires_after(std::chrono::seconds(30));// Set the timeout.
        http::async_read(stream_, buffer_, req_,// Read a request
            beast::bind_front_handler(&session::on_read, shared_from_this()));
    }


    void on_read(
        beast::error_code ec,
        std::size_t bytes_transferred)
    {
        boost::ignore_unused(bytes_transferred);        
        if(ec == http::error::end_of_stream)// This means client closed the connection
            return do_close();

        if(ec)
            return;
       std::cout<<req_<<std::endl;
       control.process_http_request(req_);
        send_response(control.get_response());// Send the response
    }

    void send_response(http::message_generator&& msg)
    {
        bool keep_alive = msg.keep_alive();

        beast::async_write(// Write the response
            stream_,
            std::move(msg),
            beast::bind_front_handler(
                &session::on_write, shared_from_this(), keep_alive));
    }

    void on_write(bool keep_alive,
        beast::error_code ec,
        std::size_t bytes_transferred)
    {
        boost::ignore_unused(bytes_transferred);

        if(ec)
            return;

        if(! keep_alive){
            return do_close();
        }
        do_read();
    }

    void do_close()
    {
        // Send a TCP shutdown
        beast::error_code ec;
        stream_.socket().shutdown(tcp::socket::shutdown_send, ec);

        // At this point the connection is closed gracefully
    }

private:
    Controller control;
};

//------------------------------------------------------------------------------

// Accepts incoming connections and launches the sessions
class listener : public std::enable_shared_from_this<listener>
{
    std::string confileName;
    net::io_context& ioc_;
    tcp::acceptor acceptor_;


public:
    listener( net::io_context& ioc, tcp::endpoint endpoint, const std::string &confileName_)
        : ioc_(ioc), acceptor_(net::make_strand(ioc)), confileName(confileName_)
    {
        beast::error_code ec;

        // Open the acceptor
        acceptor_.open(endpoint.protocol(), ec);
        if(ec){
            return;
        }

        acceptor_.set_option(net::socket_base::reuse_address(true), ec);// Allow address reuse
        if(ec){
            return;
        }

        acceptor_.bind(endpoint, ec);// Bind to the server address
        if(ec){
            return;
        }     
        acceptor_.listen(// Start listening for connections
            net::socket_base::max_listen_connections, ec);
        if(ec){
            return;
        }
    }

    void run()// Start accepting incoming connections
    {
        do_accept();
    }

private:

    void do_accept(){
        acceptor_.async_accept(// The new connection gets its own strand
            net::make_strand(ioc_),
            beast::bind_front_handler(
                &listener::on_accept,
                shared_from_this()));
    }

    void
    on_accept(beast::error_code ec, tcp::socket socket)
    {
        if(ec){
            return; // To avoid infinite loop
        }
        else{
            std::make_shared<session>(// Create the session and run it
                std::move(socket), confileName)->run();
        }

        // Accept another connection
        do_accept();
    }
};


void AsyncServer::run(const std::string &serverConfileName)
{
    // Create and launch a listening port
    std::make_shared<listener>(*ioc,
    endpoint_, serverConfileName
    )->run();

    // Run the I/O service on the requested number of threads
//  std::vector<std::thread> v;
//   v.reserve(threads - 1);
// for(auto i = threads - 1; i > 0; --i)
//     v.emplace_back(
//    [&ioc]
//    {
//        ioc.run();
//    });

    ioc->run();
}

AsyncServer::AsyncServer(char **args)
{
    qDebug() << "AsyncServer constructor";
    auto const address = net::ip::make_address(args[1]);
    auto const port = static_cast<unsigned short>(std::atoi(args[2]));
    auto const threads = std::max<int>(1, std::atoi(args[3]));

    ioc = std::shared_ptr<net::io_context> (new net::io_context{threads});// The io_context is required for all I/O
    endpoint_ = tcp::endpoint{address, port};
    qDebug() << "AsyncServer constructor finished";
}
