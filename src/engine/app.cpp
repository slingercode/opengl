#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include <vector>

#include "app.hpp"
#include "mesh.hpp"
#include "shader.hpp"

using namespace Engine;
using namespace Engine::State;

App::App() { window = std::make_unique<Window>(); }

App::~App() {
  std::cout << "App clear" << std::endl;

  glDeleteVertexArrays(meshes.size(), VAOs.data());
  glDeleteBuffers(meshes.size(), VBOs.data());

  meshes.clear();
  VAOs.clear();
  VAOs.clear();

  window = nullptr;
}

void App::processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void App::initTestbed() {
  // clang-format off
  meshes.push_back(
    std::make_unique<Mesh>(std::vector<float>{
      -0.9f, -0.5f, 0.0f,
      -0.0f, -0.5f, 0.0f,
      -0.45f, 0.5f, 0.0f,
    })
  );
  // clang-format on

  auto orangeShader = std::make_shared<Shader>(vertexPath, fragmentOrangePath);
  meshes[0]->shader = orangeShader;

  // clang-format off
  meshes.push_back(
    std::make_unique<Mesh>(std::vector<float>{
      0.0f, -0.5f, 0.0f,
      0.9f, -0.5f, 0.0f,
      0.45f, 0.5f, 0.0f
    })
  );
  // clang-format on

  auto yellowShader = std::make_shared<Shader>(vertexPath, fragmentYellowPath);
  meshes[1]->shader = yellowShader;

  VAOs.resize(meshes.size());
  VBOs.resize(meshes.size());

  glGenVertexArrays(meshes.size(), VAOs.data());
  glGenBuffers(meshes.size(), VBOs.data());

  for (size_t i = 0; i < meshes.size(); i++) {
    meshes[i]->VAO = VAOs[i];
    meshes[i]->VBO = VBOs[i];
    meshes[i]->init();
  }
}

void App::loop() {
  while (!glfwWindowShouldClose(window->ref)) {
    processInput(window->ref);

    glClearColor(Window::BG_COLOR, Window::BG_COLOR, Window::BG_COLOR, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (const auto &mesh : meshes) {
      mesh->render();
    }

    glfwSwapBuffers(window->ref);
    glfwPollEvents();
  }
}
