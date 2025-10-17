#pragma once

#include <string>

namespace Engine {
namespace Utils {
const std::string readFile(const char *filepath);

unsigned char *loadImage(const char *imagePath);

void freeImageData(unsigned char *data);
} // namespace Utils
} // namespace Engine
