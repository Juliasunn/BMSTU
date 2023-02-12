#ifndef ASYNCSERVER_H
#define ASYNCSERVER_H
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

// Handles an HTTP server connection

#include <controller.h>


#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/config.hpp>
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include <iostream>

#include <QDebug>

#include  <boost/beast/http/serializer.hpp>
#include  <strstream>
#include "../BL/Config/serverconfig.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = boost::beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>




class AsyncServer
{
public:
    void run(const std::string &serverConfileName);
    AsyncServer(char **args);
private:
    std::shared_ptr<net::io_context> ioc;// The io_context is required for all I/O
    tcp::endpoint endpoint_;
};

#endif // ASYNCSERVER_H
