#include <iostream>

#include "texture.hpp"
#include "utils.hpp"

using namespace Engine::State;

Texture::Texture(const char *textureSource) {
  unsigned char *data = Utils::loadImage(textureSource);
  if (data) {
    std::cout << "DATA" << std::endl;
  } else {
    std::cout << "NO DATA" << std::endl;
  }

  Utils::freeImageData(data);
}

Texture::~Texture() { std::cout << "Texture clear" << std::endl; }
