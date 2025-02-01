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

class Session : public std::enable_shared_from_this<Session> {
    beast::tcp_stream stream_;
    beast::flat_buffer buffer_;
    http::request<http::string_body> req_;

public:
    explicit Session(tcp::socket&& socket)
        : stream_(std::move(socket)) {}

    void run() {
        http::async_read(stream_, buffer_, req_,
            [self = shared_from_this()](beast::error_code ec, std::size_t bytes_transferred) {
                self->handle_request(ec);
            });
    }

    void handle_request(beast::error_code ec) {
        if(ec) {
            std::cerr << "Error: " << ec.message() << std::endl;
            return;
        }

        http::response<http::string_body> res;
        res.version(req_.version());
        res.keep_alive(false);

        if(req_.method() == http::verb::get && req_.target() == "/api/products") {
            res.result(http::status::ok);
            res.set(http::field::server, "Boost Beast Server");
            res.set(http::field::content_type, "application/json");
            res.body() = R"({"message": "this is a list of products"})";
        } else {
            res.result(http::status::not_found);
            res.set(http::field::content_type, "text/plain");
            res.body() = "Not Found";
        }

        res.prepare_payload();

        http::async_write(stream_, res,
            [self = shared_from_this()](beast::error_code ec, std::size_t) {
                self->stream_.socket().shutdown(tcp::socket::shutdown_send, ec);
            });
    }
};



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

int main() {
    try {
        Server server(8080);
        std::cout << "Server running on port 8080..." << std::endl;
        server.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}