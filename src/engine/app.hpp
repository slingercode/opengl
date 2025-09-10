#pragma once

#include <memory>

#include "state.hpp"

namespace Engine {
class App {
private:
  void processInput(GLFWwindow *window);

public:
  std::unique_ptr<Engine::State::Window> window;

  App();
  ~App();

  void loop();
};
} // namespace Engine
