// server.cc
#include "../include/session.h"
#include "../include/server.h"
#include <boost/beast/core.hpp>
#include <memory>
#include <iostream>

namespace beast = boost::beast;
namespace net = boost::asio;

using tcp = boost::asio::ip::tcp;

Server::Server(unsigned short port) : acceptor_(ioc_, {tcp::v4(), port}) {
    accept();
}

void Server::run() {
    ioc_.run();
}

void Server::accept() {
    acceptor_.async_accept(
        [this](beast::error_code ec, tcp::socket socket) {
            if(!ec) {
                std::make_shared<session::Session>(std::move(socket))->run();
            } else {
                std::cerr << "Accept error: " << ec.message() << std::endl; // Added error logging
            }
            accept();
        });
}
