// File: src/main.cc
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <iostream>
#include <memory>
#include <string>

#include "listener.h"
#include "session.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

int main()
{
    try
    {
        auto const address = net::ip::make_address("0.0.0.0");
        auto const port = static_cast<unsigned short>(8080);

        net::io_context ioc{1};

        auto listener = std::make_shared<Listener>(ioc, tcp::endpoint{address, port});
        listener->start();

        ioc.run();
    }
    catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
