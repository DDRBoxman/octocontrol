cmake_minimum_required(VERSION 3.10)
project(octocontrol)

set(CMAKE_CXX_STANDARD 11)

find_package(glfw3 3.2 REQUIRED)
find_package(OpenGL REQUIRED)

set(NANOVG_SOURCE
        ./deps/nanovg/src/nanovg.c)

include_directories(
        ./deps/nanovg/src
        ${GLFW_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIR})
include_directories(${CMAKE_BINARY_DIR}/glxw/include)

set(SOURCE_FILES main.cpp)

link_libraries(glfw ${OPENGL_gl_LIBRARY})

add_executable(octocontrol
        ${NANOVG_SOURCE}
        ${NANOVG_HEADERS}
        ${SOURCE_FILES})

file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
