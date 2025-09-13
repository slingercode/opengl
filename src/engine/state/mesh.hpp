#pragma once

#include <memory>
#include <vector>

#include "shader.hpp"

namespace Engine {
namespace State {
class Mesh {
public:
  unsigned int VAO, VBO;

  std::vector<float> vertices;
  std::shared_ptr<Engine::State::Shader> shader;

  Mesh(std::vector<float> vertices);

  ~Mesh();

  void init();

  void render();
};
} // namespace State
} // namespace Engine
