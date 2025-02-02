#ifndef SESSION_H
#define SESSION_H

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <memory>

namespace beast = boost::beast;
namespace http = beast::http;
namespace asio = boost::asio;
using tcp = asio::ip::tcp;

namespace session {
    class Session : public std::enable_shared_from_this<Session> {
    public:
        explicit Session(tcp::socket&& socket);

        void run();
        void handle_request(beast::error_code ec);

    private:
        beast::tcp_stream stream_;
        beast::flat_buffer buffer_;
        http::request<http::string_body> req_;
    };
}

#endif // SESSION_H
