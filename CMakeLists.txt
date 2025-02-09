# File: CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(boost_api LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
endif()

find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)

# Correctly find headers in include/
include_directories(include)

file(GLOB_RECURSE SOURCES
    "src/*.cc"
    "src/*.cpp"
     "src/api/controllers/*.cc"
)


add_executable(${PROJECT_NAME} ${SOURCES})



target_link_libraries(${PROJECT_NAME}
    Boost::system
    OpenSSL::SSL
    OpenSSL::Crypto
)

target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})