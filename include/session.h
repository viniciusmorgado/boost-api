// File: include/session.h
#ifndef SESSION_H
#define SESSION_H

#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <memory>

#include "request_handler.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
public:
  Session(tcp::socket &&socket);
  void start();

private:
  void do_read();
  void do_write(http::response<http::string_body> &&res);

  tcp::socket socket_;
  beast::flat_buffer buffer_;
  http::request<http::string_body> req_;
  RequestHandler request_handler_;
};
#endif