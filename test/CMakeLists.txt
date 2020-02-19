project(test)
file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "*.h")

add_library(test ${SOURCES} ${HEADERS})