#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <iostream>

#include "window.hpp"

using namespace Engine::State;

Window::Window() {
  ref = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL", nullptr, nullptr);
  if (ref == nullptr) {
    std::cerr << "Failed to create a GLFW window" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(ref);
}

Window::~Window() {
  std::cout << "Window clear" << std::endl;

  ref = nullptr;
}

void Window::framebufferSizeCallback(    //
    [[maybe_unused]] GLFWwindow *window, //
    int width,                           //
    int height                           //
) {
  glViewport(0, 0, width, height);
}
