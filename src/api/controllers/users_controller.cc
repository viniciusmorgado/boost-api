// File: src/api/controllers/users_controller.cc
#include "api/controllers/users_controller.h"
#include <iostream>

namespace api::controllers
{

    void UsersController::handle_request(http::request<http::string_body> &req,
                                         http::response<http::string_body> &res)
    {
        res.version(req.version());
        res.set(http::field::content_type, "application/json");

        if (req.method() == http::verb::post && req.target() == "/api/users")
        {
            res.result(http::status::created);
            res.body() = R"({"message": "user created successfully"})";
        }
        else if (req.method() == http::verb::get && req.target() == "/api/users")
        {
            res.result(http::status::ok);
            res.body() = R"({"message": "this is a list of users"})";
        }
        else if (req.method() == http::verb::put &&
                 req.target().starts_with("/api/users/"))
        {
            res.result(http::status::ok);
            res.body() = R"({"message": "user updated successfully"})";
        }
        else if (req.method() == http::verb::delete_ &&
                 req.target().starts_with("/api/users/"))
        {
            res.result(http::status::ok);
            res.body() = R"({"message": "user deleted successfully"})";
        }
        else
        {
            res.result(http::status::not_found);
            res.body() = R"({"error": "Not Found"})";
        }
        res.prepare_payload();
    }

} // namespace api::controllers