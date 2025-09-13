#pragma once

#define LOG_SIZE 512

namespace Engine {
namespace State {
class Shader {
  int success;
  char infoLog[LOG_SIZE];

  unsigned int vertexShader, fragmentShader;

  unsigned int compileShader(const char *shaderSource, int type);

  void linkShaders();

public:
  unsigned int program;

  Shader(const char *vertexShaderPath, const char *fragmentShaderPath);
  ~Shader();
};
} // namespace State
} // namespace Engine
