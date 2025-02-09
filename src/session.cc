// File: src/session.cc
#include "../include/session.h"
#include <iostream>

Session::Session(tcp::socket &&socket) : socket_(std::move(socket)), request_handler_{} {}

void Session::start() { do_read(); }

void Session::do_read()
{
    auto self(shared_from_this());
    http::async_read(
        socket_, buffer_, req_,
        [self](beast::error_code ec, std::size_t /*bytes_transferred*/)
        {
            if (!ec)
            {
                auto response = self->request_handler_.handle_request(std::move(self->req_));
                self->do_write(std::move(response));
            }
            else if (ec != http::error::end_of_stream)
            {
                std::cerr << "Error reading request: " << ec.message() << std::endl;
            }
        });
}

void Session::do_write(http::response<http::string_body> &&res)
{
    auto self(shared_from_this());

    http::async_write(socket_, res,
                      [self](beast::error_code ec, std::size_t bytes_transferred)
                      {
                          if (!ec)
                          {
                              self->req_ = {};
                              self->do_read();
                          }
                          else
                          {
                              std::cerr << "Error writing response: " << ec.message() << std::endl;
                          }

                          if (ec == http::error::end_of_stream || ec == net::error::connection_reset || ec == net::error::broken_pipe)
                          {
                              return;
                          }
                      });
}