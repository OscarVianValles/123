#include "helpers.hpp"

std::list<std::string> tokenize(std::string x, char y) {
  std::list<std::string> tokens;
  std::stringstream input(x);
  std::string holder;

  while (getline(input, holder, y)) {
    tokens.push_back(holder);
  }

  return tokens;
}
