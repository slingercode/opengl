#pragma once

#include <GLFW/glfw3.h>

namespace Engine {
namespace State {
class Window {
public:
  static const int WIDTH = 800;
  static const int HEIGHT = 800;
  static constexpr float BG_COLOR = 16.0f / 255.0f;

  GLFWwindow *ref;

  Window();
  ~Window();

  // clang-format off
  static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
  // clang-format on
};
} // namespace State
} // namespace Engine
