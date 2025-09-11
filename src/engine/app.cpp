#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>

#include "app.hpp"
#include "state/shader.hpp"

using namespace Engine;
using namespace Engine::State;

App::App() { window = std::make_unique<Window>(); }

App::~App() { std::cout << "App clear" << std::endl; }

void App::processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

const std::string App::readFile(const char *path) {
  std::ifstream file(path);

  if (!file.is_open()) {
    return "";
  }

  const std::string content(                  //
      (std::istreambuf_iterator<char>(file)), //
      std::istreambuf_iterator<char>()        //
  );

  file.close();

  return content;
}

void App::loop() {
  const std::string vertexShaderSource = App::readFile(vertexPath);
  const std::string fragmentShaderSource = App::readFile(fragmentPath);

  auto orangeShader = std::make_unique<Shader>( //
      vertexShaderSource.c_str(),               //
      fragmentShaderSource.c_str()              //
  );

  // Vertex data
  float vertices[] = {
      -0.5f, -0.5f, 0.0f, //
      0.5f, -0.5f, 0.0f,  //
      0.0f, 0.5f, 0.0f    //
  };

  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);

  while (!glfwWindowShouldClose(window->ref)) {
    processInput(window->ref);

    glClearColor(Window::BG_COLOR, Window::BG_COLOR, Window::BG_COLOR, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(orangeShader->program);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window->ref);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
}
