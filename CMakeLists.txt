cmake_minimum_required(VERSION 3.30)

project(OpenGL)

set(CMAKE_C_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")

set(GLFW_SDK_PATH "/opt/homebrew/Cellar/glfw/3.4")

file(GLOB_RECURSE SRC "src/*.c" "third-party/*.c")

file(GLOB_RECURSE HEADER_DIRS RELATIVE ${CMAKE_SOURCE_DIR} "src/*.h")
foreach(_headerFile ${HEADER_DIRS})
    get_filename_component(_dir ${_headerFile} PATH)
    list(APPEND HEADER_DIR_LIST ${_dir})
endforeach()

list(REMOVE_DUPLICATES HEADER_DIR_LIST)

include_directories(${HEADER_DIR_LIST} ${GLFW_SDK_PATH}/include "third-party/")

link_directories(${GLFW_SDK_PATH}/lib "third-party/")

# Debug mode configuration
add_executable(debug ${SRC})
target_link_libraries(debug glfw3)

if (APPLE)
    target_link_libraries(debug "-framework Cocoa" "-framework IOKit")
endif()

# Release mode configuration
add_executable(release ${SRC})
target_link_libraries(release glfw3)

if (APPLE)
    target_link_libraries(release "-framework Cocoa" "-framework IOKit")
endif()
