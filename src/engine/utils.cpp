#include <fstream>
#include <iterator>

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
