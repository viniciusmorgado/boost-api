#include "../include/session.h"
#include <boost/beast/http.hpp>
#include <iostream>

namespace http = beast::http;

using tcp = boost::asio::ip::tcp;

namespace session {
    void Session::run() {
            http::async_read(stream_, buffer_, req_,
                [self = shared_from_this()](beast::error_code ec, std::size_t bytes_transferred) {
                    self->handle_request(ec);
                });
    }

        void Session::handle_request(beast::error_code ec) {
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
}
