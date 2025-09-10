#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>

#include "app.hpp"
#include "engine.hpp"
#include "state.hpp"

using namespace Engine::State;

void Engine::run() {
  const int glfwInitializated = glfwInit();
  if (glfwInitializated != GLFW_TRUE) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  auto app = std::make_unique<Engine::App>();

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwTerminate();

    std::cerr << "Failed to initialize GLAD" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  int framebuffer_width, framebuffer_height;
  glfwGetFramebufferSize( //
      app->window->ref,   //
      &framebuffer_width, //
      &framebuffer_height //
  );

  glViewport(0, 0, framebuffer_width, framebuffer_height);

  glfwSetFramebufferSizeCallback(       //
      app->window->ref,                 //
      Window::framebuffer_size_callback //
  );

  app->loop();

  glfwTerminate();
}
