// File: src/listener.cc
#include "../include/listener.h"
#include <iostream>
#include "../include/session.h"

Listener::Listener(net::io_context &ioc, tcp::endpoint endpoint)
    : ioc_(ioc), acceptor_(ioc)
{
    beast::error_code ec;

    acceptor_.open(endpoint.protocol(), ec);
    if (ec)
    {
        std::cerr << "Error opening acceptor: " << ec.message() << std::endl;
        return;
    }

    acceptor_.set_option(net::socket_base::reuse_address(true), ec);
    if (ec)
    {
        std::cerr << "Error setting reuse_address: " << ec.message() << std::endl;
        return;
    }

    acceptor_.bind(endpoint, ec);
    if (ec)
    {
        std::cerr << "Error binding acceptor: " << ec.message() << std::endl;
        return;
    }

    acceptor_.listen(net::socket_base::max_listen_connections, ec);
    if (ec)
    {
        std::cerr << "Error listening: " << ec.message() << std::endl;
        return;
    }
}

void Listener::start() { do_accept(); }

void Listener::do_accept()
{
    acceptor_.async_accept(
        ioc_, [self = shared_from_this()](beast::error_code ec,
                                          tcp::socket socket)
        {
        if (!ec) {
          std::make_shared<Session>(std::move(socket))->start();
        } else {
          std::cerr << "Error accepting connection: " << ec.message()
                    << std::endl;
        }
        self->do_accept(); });
}