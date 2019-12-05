#include "helpers.hpp"

std::list<std::string> tokenize(std::string x) {
  std::list<std::string> tokens;
  std::stringstream input(x);
  std::string holder;

  while (getline(input, holder, '/')) {
    tokens.push_back(holder);
  }

  return tokens;
}
