// File: include/api/controllers/users_controller.h
#ifndef USERS_CONTROLLER_H
#define USERS_CONTROLLER_H

#include <boost/beast/http.hpp>
#include <string>

namespace beast = boost::beast;
namespace http = beast::http;

namespace api::controllers
{

    class UsersController
    {
    public:
        void handle_request(http::request<http::string_body> &req,
                            http::response<http::string_body> &res);
    };

} // namespace api::controllers
#endif