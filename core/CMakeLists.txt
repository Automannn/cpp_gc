project(core)
file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "*.h")

add_library(core ${SOURCES} ${HEADERS})