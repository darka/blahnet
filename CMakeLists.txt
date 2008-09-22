cmake_minimum_required(VERSION 2.4)
project(NetNet)

set(CMAKE_CXX_FLAGS "-std=c++98 -Wall -Wextra -pedantic -ggdb3")
include_directories(src)

file(GLOB main_sources src/*.cpp)
file(GLOB server_sources server/*.cpp)
file(GLOB client_sources client/*.cpp)
add_library(netnet STATIC ${main_sources})

# for testing
add_executable(netnet-server ${server_sources})
add_executable(netnet-client ${client_sources})
target_link_libraries(netnet-server netnet)
target_link_libraries(netnet-client netnet)

