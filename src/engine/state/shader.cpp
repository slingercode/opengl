#include <glad/glad.h>

#include <iostream>

#include "shader.hpp"

using namespace Engine::State;

Shader::Shader(const char *vertexSource, const char *fragmentSource) {
  vertexShader = compileShader(vertexSource, GL_VERTEX_SHADER);
  fragmentShader = compileShader(fragmentSource, GL_FRAGMENT_SHADER);

  Shader::linkShaders();
}

Shader::~Shader() {
  std::cout << "Shader clear" << std::endl;

  glDeleteProgram(program);
}

unsigned int Shader::compileShader(const char *shaderSource, int type) {
  unsigned int shader = glCreateShader(type);

  glShaderSource(shader, 1, &shaderSource, NULL);
  glCompileShader(shader);

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, LOG_SIZE, NULL, infoLog);
    std::cout << "Shader compilation: " << infoLog << std::endl;
  }

  return shader;
}

void Shader::linkShaders() {
  program = glCreateProgram();

  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);

  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, LOG_SIZE, NULL, infoLog);
    std::cout << "Shader linking: " << infoLog << std::endl;
  }

  glUseProgram(program);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}
