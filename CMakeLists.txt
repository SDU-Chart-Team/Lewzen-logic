cmake_minimum_required(VERSION 3.21)
project(mind)

set(CMAKE_CXX_STANDARD 14)

add_executable(mind main.cpp test.cpp
        component.cpp component.h
        canvas.cpp canvas.h
        value.h rectangle.h rectangle.cpp circle.h circle.cpp
        parashape.cpp parashape.h circle.cpp circle.h oval.cpp oval.h hexagon.cpp hexagon.h
        diamond.cpp diamond.h triangle.cpp triangle.h)

