#pragma once

#include <string>

#define LOG_SIZE 512

namespace Engine {
namespace State {
class Shader {
private:
  int success;
  char infoLog[LOG_SIZE];

  unsigned int program;
  unsigned int vertexShader, fragmentShader;

  unsigned int compileShader(const char *shaderSource, int type);

  void linkShaders();

public:
  Shader(const char *vertexShaderPath, const char *fragmentShaderPath);
  ~Shader();

  void use();

  void setInt(const std::string &name, int value) const;
  void setBool(const std::string &name, bool value) const;
  void setFloat(const std::string &name, float value) const;
};
} // namespace State
} // namespace Engine
