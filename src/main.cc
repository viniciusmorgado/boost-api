// File: src/main.cc (The ONLY file that needs modification)
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <thread> // Include for std::thread
#include <vector>

#include "listener.h"
#include "session.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

int main() {
    try {
        auto const address = net::ip::make_address("0.0.0.0");
        auto const port = static_cast<unsigned short>(8080);

        net::io_context ioc; // Removed the thread count {1}

        auto listener = std::make_shared<Listener>(ioc, tcp::endpoint{address, port});
        listener->start();

        // Create a vector of threads to run the io_context.
        std::vector<std::thread> threads;
        int num_threads = std::thread::hardware_concurrency(); // Use number of cores
        if (num_threads == 0) {
          num_threads = 4; // A reasonable default if hardware_concurrency() fails
        }
        threads.reserve(num_threads);

        for(int i = 0; i < num_threads; ++i) {
            threads.emplace_back([&ioc] { ioc.run(); }); // Each thread calls ioc.run()
        }

        // Keep the main thread alive (but don't call ioc.run() here).
        for (auto& t : threads) {
            t.join(); // Wait for all threads to finish (which they won't, unless you stop the ioc)
        }


    } catch (std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}