#include <glad/glad.h>

#include <iostream>

#include "mesh.hpp"

using namespace Engine::State;

Mesh::Mesh(std::vector<float> v) : vertices(v) {}

Mesh::~Mesh() {
  std::cout << "Mesh clear" << std::endl;

  vertices.clear();
}

// I don't know how to call this ATM
void Mesh::init() {
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
      vertices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void *)0);
  glEnableVertexAttribArray(0);
}

void Mesh::render() {
  glUseProgram(shader->program);
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}
