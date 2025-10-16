#pragma once

#include <memory>
#include <vector>

#include "mesh.hpp"
#include "window.hpp"

namespace Engine {
class App {
private:
  const char *vertexPath = "../shaders/vertex.glsl";
  const char *fragmentPath = "../shaders/fragment.glsl";

  void processInput(GLFWwindow *window);

public:
  std::unique_ptr<Engine::State::Window> window;

  std::vector<unsigned int> VBOs, VAOs;
  std::vector<std::unique_ptr<Engine::State::Mesh>> meshes;

  App();
  ~App();

  void initTestbed();

  void loop();
};
} // namespace Engine
