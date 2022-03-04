cmake_minimum_required(VERSION 2.8)
project(landmark)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")

set(COMMON_SOURCES dataIO.cpp graph.cpp draw_img.cpp cs225/HSLAPixel.cpp cs225/PNG.cpp cs225/RGB_HSL.h
        cs225/lodepng/lodepng.cpp cs225/Animation.cpp)

set(TARGET_SOURCES main.cpp)

set(TEST_SOURCES tests/tests_graph.cpp catch/catch.hpp catch/catchmain.cpp)

add_executable(landmark ${TARGET_SOURCES} ${COMMON_SOURCES})

add_executable(test ${TEST_SOURCES} ${COMMON_SOURCES})
