// File: src/request_handler.cc
#include "request_handler.h"

RequestHandler::RequestHandler()
{
    routes_["GET/api/products"] = [this](auto &req, auto &res)
    { products_controller_.handle_request(req, res); };
    routes_["POST/api/products"] = [this](auto &req, auto &res)
    { products_controller_.handle_request(req, res); };
    routes_["GET/api/users"] = [this](auto &req, auto &res)
    { users_controller_.handle_request(req, res); };
    routes_["POST/api/users"] = [this](auto &req, auto &res)
    { users_controller_.handle_request(req, res); };
}

http::response<http::string_body>
RequestHandler::handle_request(http::request<http::string_body> &&req)
{
    http::response<http::string_body> res;
    std::string route_key = std::string(req.method_string()) + std::string(req.target());

    // Basic routing
    if (routes_.count(route_key))
    {
        routes_[route_key](req, res);
    }
    else if (req.target().starts_with("/api/products/") && (req.method() == http::verb::put || req.method() == http::verb::delete_))
    {
        products_controller_.handle_request(req, res);
    }
    else if (req.target().starts_with("/api/users/") && (req.method() == http::verb::put || req.method() == http::verb::delete_))
    {
        users_controller_.handle_request(req, res);
    }
    else
    {
        res.result(http::status::not_found);
        res.set(http::field::content_type, "application/json");
        res.body() = R"({"error": "API endpoint not found"})";
        res.prepare_payload();
    }

    return res;
}
