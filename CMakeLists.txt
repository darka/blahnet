cmake_minimum_required(VERSION 2.4)
project(NetNet)


include_directories(src)

file(GLOB main_sources src/*.cpp)
file(GLOB server_sources server/*.cpp)
file(GLOB client_sources client/*.cpp)
file(GLOB tests_sources tests/*.cpp)

if(WIN32)
	add_definitions(-DBLAHNET_WIN32)
endif(WIN32)

if(UNIX)
	set(CMAKE_CXX_FLAGS "-Wall -Wextra -ggdb3")
endif(UNIX)

add_library(netnet STATIC ${main_sources})

# for testing
add_executable(netnet-server ${server_sources})
add_executable(netnet-client ${client_sources})
add_executable(test-all ${tests_sources})

set(LINK_LIBS netnet boost_signals)
set(WIN32_LINK_LIBS ${LINK_LIBS} wsock32)

if(WIN32)
	target_link_libraries(netnet-server ${WIN32_LINK_LIBS})
	target_link_libraries(test-all ${WIN32_LINK_LIBS})
	target_link_libraries(netnet-client ${WIN32_LINK_LIBS})
else(WIN32)
	target_link_libraries(netnet-server ${LINK_LIBS})
	target_link_libraries(netnet-client ${LINK_LIBS})
	target_link_libraries(test-all ${LINK_LIBS})
endif(WIN32)
