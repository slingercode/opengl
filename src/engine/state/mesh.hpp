#pragma once

#include <memory>
#include <vector>

#include "shader.hpp"

namespace Engine {
namespace State {
class Mesh {
private:
  const int VERTEX_POSITION = 0;
  const int VERTEX_COLOR = 1;

  const char *texturePath = "";

  void setVertexFloatAttribute( //
      int position,             //
      int size,                 //
      int stride,               //
      const void *pointer       //
  );

  void setVertexPositionAttribute();
  void setVertexColorAttribute();

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
