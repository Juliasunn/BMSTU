#include <QCoreApplication>

#include </home/julia/boost/boost/beast/core.hpp>
#include </home/julia/boost/boost/beast/http.hpp>
#include </home/julia/boost/boost/beast/version.hpp>
#include </home/julia/boost/boost/asio.hpp>

#include </home/julia/boost/boost/json.hpp>
#include </home/julia/boost/boost/json/value.hpp>
#include <boost/json/src.hpp>

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>

#include <QDebug>

#include "asyncserver.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

int main(int argc, char* argv[])
{
    qDebug() << "start main";
    AsyncServer s = AsyncServer(argv);
    s.run(std::string(argv[4]));
    return 0;
}
