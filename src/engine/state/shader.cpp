#include <glad/glad.h>

#include <iostream>

#include "shader.hpp"
#include "utils.hpp"

using namespace Engine::State;
using namespace Engine::Utils;

Shader::Shader(const char *vertexShaderPath, const char *fragmentShaderPath) {
  const std::string vertexSource = readFile(vertexShaderPath);
  const std::string fragmentSource = readFile(fragmentShaderPath);

  const char *vs = vertexSource.c_str();
  const char *fs = fragmentSource.c_str();

  vertexShader = compileShader(vs, GL_VERTEX_SHADER);
  fragmentShader = compileShader(fs, GL_FRAGMENT_SHADER);

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

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void Shader::use() { glUseProgram(program); }

void Shader::setInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}

void Shader::setBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(program, name.c_str()), (int)value);
}

void Shader::setFloat(const std::string &name, float value) const {
  glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}
