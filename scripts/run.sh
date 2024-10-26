#!/bin/sh

if [ "$#" == 1 ]; then
  GLFW_SDK_PATH="$1"
else
  GLFW_SDK_PATH=""
fi

mkdir -p build && cd build

if [ "$GLFW_SDK_PATH" != "" ]; then
  cmake -DCMAKE_BUILD_TYPE=debug -DGLFW_SDK_PATH="$GLFW_SDK_PATH" ..
else
  cmake -DCMAKE_BUILD_TYPE=debug ..
fi

cmake --build . --target run
