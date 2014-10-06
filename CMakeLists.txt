cmake_minimum_required(VERSION 2.8)

project(img2stl)

add_definitions(-std=c++14)

add_executable(decompress main.cpp deCompress.cpp)


