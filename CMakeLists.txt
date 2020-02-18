cmake_minimum_required(VERSION 3.15)
project(automannn_gc)
set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "*.h")

add_subdirectory(core)

add_executable(automannn_gc ${SOURCES} ${HEADERS})