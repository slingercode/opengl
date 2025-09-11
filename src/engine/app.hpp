#pragma once

#include <memory>

#include "state/window.hpp"

namespace Engine {
class App {
private:
  const char *vertexPath = "../shaders/vertex.glsl";
  const char *fragmentPath = "../shaders/fragment.glsl";

  void processInput(GLFWwindow *window);

  const std::string readFile(const char *path);

public:
  std::unique_ptr<Engine::State::Window> window;

  App();
  ~App();

  void loop();
};
} // namespace Engine
