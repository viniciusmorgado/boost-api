// server.h
#ifndef SERVER_H
#define SERVER_H

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>

class Server {
private:
    boost::asio::io_context ioc_;
    boost::asio::ip::tcp::acceptor acceptor_;
    void accept();

public:
    Server(unsigned short port);
    void run();
};

#endif // SERVER_H