// File: src/api/controllers/products_controller.cc
#include "api/controllers/products_controller.h"
#include <iostream>

namespace api::controllers
{

    void ProductsController::handle_request(http::request<http::string_body> &req,
                                            http::response<http::string_body> &res)
    {
        res.version(req.version());
        res.set(http::field::content_type, "application/json");

        if (req.method() == http::verb::post && req.target() == "/api/products")
        {
            res.result(http::status::created);
            res.body() = R"({"message": "product created successfully"})";
        }
        else if (req.method() == http::verb::get && req.target() == "/api/products")
        {
            res.result(http::status::ok);
            res.body() = R"({"message": "this is a list of products"})";
        }
        else if (req.method() == http::verb::put &&
                 req.target().starts_with("/api/products/"))
        {
            res.result(http::status::ok);
            res.body() = R"({"message": "product updated successfully"})";
        }
        else if (req.method() == http::verb::delete_ &&
                 req.target().starts_with("/api/products/"))
        {
            res.result(http::status::ok);
            res.body() = R"({"message": "product deleted successfully"})";
        }
        else
        {
            res.result(http::status::not_found);
            res.body() = R"({"error": "Not Found"})";
        }
        res.prepare_payload();
    }

} // namespace api::controllers