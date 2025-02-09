// File: include/listener.h
#ifndef LISTENER_H
#define LISTENER_H

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <memory>
#include <boost/beast/http.hpp>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

class Listener : public std::enable_shared_from_this<Listener>
{
public:
    Listener(net::io_context &ioc, tcp::endpoint endpoint);
    void start();

private:
    void do_accept();

    net::io_context &ioc_;
    tcp::acceptor acceptor_;
};
#endif