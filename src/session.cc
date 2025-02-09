#include "../include/session.h"
#include <boost/beast/http.hpp>
#include <iostream>

namespace http = beast::http;

using tcp = boost::asio::ip::tcp;

namespace session {
    Session::Session(tcp::socket&& socket) : stream_(std::move(socket)) {}
    
    // break session::Session::run
    void Session::run() {
            http::async_read(stream_, buffer_, req_, [self = shared_from_this()](beast::error_code ec, std::size_t bytes_transferred) {
                if(ec) {
                    std::cerr << "Error on Session::run() - http::async_read: " << ec.message() << std::endl;
                    return;
                }
                self->handle_request(ec);
            });
            
    }
        // break session::Session::handle_request
        void Session::handle_request(beast::error_code ec) {
            
            if(ec) {
                std::cerr << "Error on void Session::handle_requests: " << ec.message() << std::endl;
                return;
            }

            http::response<http::string_body> res;
            res.version(req_.version());
            res.keep_alive(req_.keep_alive());

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

            // break session.cc:48
            http::async_write(stream_, res, [self = shared_from_this()](beast::error_code ec, std::size_t) {
                if (ec) {
                    std::cerr << "Error during async_write in handle_request: " << ec.message() << std::endl;
                }
                // break session.cc:53
                self->stream_.socket().shutdown(tcp::socket::shutdown_send, ec);
            });
        }

        Session::~Session() {
            std::cout << "~Session() called" << std::endl;
        }
}

// Internal library breakpoint
// break boost::beast::http::basic_fields<std::allocator<char> >::value_type::buffer