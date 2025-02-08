// main.cc
#include "../include/server.h"
#include <cstdlib>
#include <iostream>

int main() {
    try {
        Server server(8080);
        std::cout << "Server running on port 8080..." << std::endl;
        server.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
