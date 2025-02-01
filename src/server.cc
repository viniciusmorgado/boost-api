#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class Server {
    net::io_context ioc_;
    tcp::acceptor acceptor_;

public:
    Server(unsigned short port)
        : acceptor_(ioc_, {tcp::v4(), port}) {
        accept();
    }

    void run() {
        ioc_.run();
    }

private:
    void accept() {
        acceptor_.async_accept(
            [this](beast::error_code ec, tcp::socket socket) {
                if(!ec) {
                    std::make_shared<Session>(std::move(socket))->run();
                }
                accept();
            });
    }
};
