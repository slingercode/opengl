#define STB_IMAGE_IMPLEMENTATION

#include <fstream>
#include <iterator>

#include "stb_image.h"
#include "utils.hpp"

using namespace Engine;

const std::string Utils::readFile(const char *filepath) {
  std::ifstream file(filepath);

  if (!file.is_open()) {
    return "";
  }

  const std::string content(                  //
      (std::istreambuf_iterator<char>(file)), //
      std::istreambuf_iterator<char>()        //
  );

  file.close();

  return content;
}

unsigned char *Utils::loadImage(const char *imagePath) {
  int width, height, nrChannels;
  return stbi_load(imagePath, &width, &height, &nrChannels, 0);
}

void Utils::freeImageData(unsigned char *data) { stbi_image_free(data); }
