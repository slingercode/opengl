cmake_minimum_required(VERSION 3.30)

if (APPLE)
    set(GLFW_SDK_PATH "/opt/homebrew/Cellar/glfw/3.4" CACHE PATH "Path to GLFW SDK")
elseif()
    set(GLFW_SDK_PATH "" CACHE PATH "Path to GLFW SDK (set this if GLFW is installed elsewhere)")
endif()

if(NOT EXISTS ${GLFW_SDK_PATH}/include OR NOT EXISTS ${GLFW_SDK_PATH}/lib)
    message(FATAL_ERROR "Invalid path specified for GLFW_SDK_PATH: ${GLFW_SDK_PATH}")
endif()

project(OpenGL C)

# I know this is not required but im learning, actually i can
# update this this with cmake cross compile
if (CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
    set(ARCH, "arm64")
elseif()
    set(ARCH, "")
endif()

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC "src/*.c" "externals/*.c")
file(GLOB_RECURSE HEADER_DIRS RELATIVE ${CMAKE_SOURCE_DIR} "src/*.h")

foreach(_headerFile ${HEADER_DIRS})
    get_filename_component(_dir ${_headerFile} PATH)
    list(APPEND HEADER_DIR_LIST ${_dir})
endforeach()

list(REMOVE_DUPLICATES HEADER_DIR_LIST)

add_executable(opengl_exe ${SRC})

if (ARCH STREQUAL "arm64")
    target_compile_options(opengl_exe PRIVATE -arch arm64)
endif()

target_compile_options(opengl_exe PRIVATE -Wall -Wextra -pedantic)
target_include_directories(opengl_exe PRIVATE ${HEADER_DIR_LIST} ${GLFW_SDK_PATH}/include "externals/")
target_link_directories(opengl_exe PRIVATE ${GLFW_SDK_PATH}/lib "externals/")
target_link_libraries(opengl_exe glfw3)

if (APPLE)
    target_link_libraries(opengl_exe "-framework Cocoa" "-framework IOKit")
endif()

set_target_properties(opengl_exe PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/release"
)

# Custom target to build and run the executable
add_custom_target(run
    DEPENDS opengl_exe
    COMMAND $<TARGET_FILE:opengl_exe>
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
