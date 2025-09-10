#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <memory>

#include "app.hpp"
#include "state.hpp"

using namespace Engine;
using namespace Engine::State;

App::App() { window = std::make_unique<Window>(); }

App::~App() {}

void App::processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void App::loop() {
  while (!glfwWindowShouldClose(window->ref)) {
    processInput(window->ref);

    glClearColor(Window::BG_COLOR, Window::BG_COLOR, Window::BG_COLOR, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window->ref);
    glfwPollEvents();
  }
}
