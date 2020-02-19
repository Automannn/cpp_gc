cmake_minimum_required(VERSION 3.15)
project(automannn_gc)
set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "*.h")

file(GLOB SOURCES1 "core/*.cpp")
file(GLOB HEADERS1 "core/*.h")


file(GLOB SOURCES2 "test/*.cpp")
file(GLOB HEADERS2 "test/*.h")

add_subdirectory(core)
add_subdirectory(test)


add_executable(automannn_gc ${SOURCES} ${HEADERS} ${SOURCES1} ${HEADERS1} ${SOURCES2} ${HEADERS2})