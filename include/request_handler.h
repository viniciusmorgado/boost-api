// File: include/request_handler.h
#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <boost/beast/http.hpp>
#include "api/controllers/products_controller.h"
#include "api/controllers/users_controller.h"
#include <map>
#include <functional>

namespace beast = boost::beast;
namespace http = beast::http;

class RequestHandler
{
public:
    RequestHandler();
    http::response<http::string_body>
    handle_request(http::request<http::string_body> &&req);

private:
    api::controllers::ProductsController products_controller_;
    api::controllers::UsersController users_controller_;
    std::map<std::string, std::function<void(http::request<http::string_body> &, http::response<http::string_body> &)>> routes_;
};
#endif