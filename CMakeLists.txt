cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TARGET opengl)
set(GLFW_DIR /opt/homebrew/Cellar/glfw/3.4)

project(${TARGET} CXX)

file(
    GLOB
    SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/*.cpp
)

add_executable(${TARGET} ${SOURCE_FILES})

target_compile_options(${TARGET} PRIVATE -Wall -Wextra -pedantic)

target_include_directories(
    ${TARGET}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine
    ${GLFW_DIR}/include
)

find_library(COCOA_FRAMEWORK Cocoa REQUIRED)
find_library(OPENGL_FRAMEWORK OpenGL REQUIRED)
find_library(IOKIT_FRAMEWORK IOKit REQUIRED)

target_link_libraries(
    ${TARGET}
    PRIVATE
    ${GLFW_DIR}/lib/libglfw3.a
    ${COCOA_FRAMEWORK}
    ${OPENGL_FRAMEWORK}
    ${IOKIT_FRAMEWORK}
)
