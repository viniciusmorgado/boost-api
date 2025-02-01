#include <boost/beast/core.hpp>

namespace beast = boost::beast;

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
};
