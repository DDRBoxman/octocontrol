cmake_minimum_required(VERSION 3.9)
project(octocontrol)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 3.2 REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(./deps/cpr)

set(NANOVG_SOURCE
        ./deps/nanovg/src/nanovg.c)

include_directories(
        ./deps/nanovg/src
        ./deps/json
        ${GLFW_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIR})
include_directories(${CMAKE_BINARY_DIR}/glxw/include)
include_directories(${CPR_INCLUDE_DIRS})

set(SOURCE_FILES src/main.cpp src/OctoPrintClient.cpp src/OctoPrintClient.h src/UI/Widget.cpp src/UI/Widget.h src/UI/TextWidget.cpp src/UI/TextWidget.h src/UI/ButtonWidget.cpp src/UI/ButtonWidget.h src/Globals.h src/UI/VectorButtonWidget.cpp src/UI/VectorButtonWidget.h src/UI.h)

link_libraries(glfw cpr ${OPENGL_gl_LIBRARY})

add_executable(octocontrol
        ${NANOVG_SOURCE}
        ${NANOVG_HEADERS}
        ${SOURCE_FILES})

file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
