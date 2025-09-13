#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>

#include "app.hpp"
#include "engine.hpp"

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

  // The application needs to be created first in order to create
  // the OpenGL context on the window
  auto app = std::make_unique<App>();

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwTerminate();

    std::cerr << "Failed to initialize GLAD" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  int framebufferWidth, framebufferHeight;
  glfwGetFramebufferSize( //
      app->window->ref,   //
      &framebufferWidth,  //
      &framebufferHeight  //
  );

  glViewport(0, 0, framebufferWidth, framebufferHeight);

  glfwSetFramebufferSizeCallback(     //
      app->window->ref,               //
      Window::framebufferSizeCallback //
  );

  app->initTestbed();

  app->loop();

  glfwTerminate();
}
