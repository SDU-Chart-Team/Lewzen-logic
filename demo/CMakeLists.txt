cmake_minimum_required (VERSION 3.5)
project(WebsocketServer)

# Set the C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(Boost_DETAILED_FAILURE_MSG ON)
set(Boost_DEBUG on)

set(BOOST_ROOT C:/Users/l'l/boost/boost_1_70_0)
set(BOOST_INCLUDEDIR ${BOOST_ROOT})
set(BOOST_LIBRARYDIR ${BOOST_ROOT}/stage/lib)
find_package(Boost COMPONENTS REQUIRED filesystem program_options)
# Enable all compiler warnings
if (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif()

# Link against pthreads under Unix systems
if (NOT MSVC AND NOT MINGW)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

# Under MinGW, statically link against the standard libraries
if (MINGW)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
endif()

# Force WebSocket++ to use 100% C++11 mode, so that it doesn't try to look for Boost
# (Note that under MinGW, Boost.Thread is still required, due to a bug in MinGW that prevents the C++11 version from being used)
add_definitions(-D_WEBSOCKETPP_CPP11_STRICT_)

# Add the third-party headers directory to the search path
include_directories(SYSTEM "${PROJECT_SOURCE_DIR}/external")

# Compile jsoncpp from source
add_library(jsoncpp STATIC ${PROJECT_SOURCE_DIR}/external/jsoncpp.cpp)

# Build the server executable
add_executable(server server.cpp WebsocketServer.cpp
		components/component.cpp components/component.h
		canvas.cpp canvas.h
		value.h components/rectangle.h components/rectangle.cpp components/circle.h components/circle.cpp
		components/parashape.cpp components/parashape.h components/circle.cpp components/circle.h components/oval.cpp components/oval.h components/hexagon.cpp components/hexagon.h
		components/diamond.cpp components/diamond.h components/triangle.cpp components/triangle.h components/line.cpp components/line.h
		respons.cpp respons.h)
target_link_libraries (server jsoncpp)

include_directories(${BOOST_ROOT})
target_link_libraries(server ${Boost_LIBRARIES})
target_link_libraries(server ws2_32)
target_link_libraries(server -lws2_32 -lwsock32 )
