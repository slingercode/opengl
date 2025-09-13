#pragma once

#include <GLFW/glfw3.h>

namespace Engine {
namespace State {
class Window {
public:
  static const unsigned int WIDTH = 1200;
  static const unsigned int HEIGHT = 800;

  // I like this color :)
  static constexpr float BG_COLOR = 16.0f / 255.0f;

  GLFWwindow *ref;

  Window();
  ~Window();

  // clang-format off
  static void framebufferSizeCallback(GLFWwindow *window, int width, int height);
  // clang-format on
};
} // namespace State
} // namespace Engine
