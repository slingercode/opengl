#include <glad/glad.h>

#include <iostream>

#include "mesh.hpp"
#include "texture.hpp"

using namespace Engine::State;

Mesh::Mesh(std::vector<float> v) : vertices(v) {}

Mesh::~Mesh() {
  std::cout << "Mesh clear" << std::endl;

  vertices.clear();
}

void Mesh::setVertexFloatAttribute( //
    int position,                   //
    int size,                       //
    int stride,                     //
    const void *pointer             //
) {
  glVertexAttribPointer( //
      position,          //
      size,              //
      GL_FLOAT,          //
      GL_FALSE,          //
      stride,            //
      pointer            //
  );

  glEnableVertexAttribArray(position);
}

void Mesh::setVertexPositionAttribute() {
  setVertexFloatAttribute( //
      VERTEX_POSITION,     //
      3,                   //
      6 * sizeof(float),   //
      (void *)0            //
  );
}

void Mesh::setVertexColorAttribute() {
  setVertexFloatAttribute(        //
      VERTEX_COLOR,               //
      3,                          //
      6 * sizeof(float),          //
      (void *)(3 * sizeof(float)) //
  );
}

// I don't know how to call this ATM
void Mesh::init() {
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(                        //
      GL_ARRAY_BUFFER,                 //
      vertices.size() * sizeof(float), //
      vertices.data(),                 //
      GL_STATIC_DRAW                   //
  );

  setVertexPositionAttribute();
  setVertexColorAttribute();

  new Texture(texturePath);
}

void Mesh::render() {
  shader->use();

  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}
