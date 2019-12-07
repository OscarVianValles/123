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

void replaceAll(std::string &source, const std::string &from,
                const std::string &to) {
  std::string newString;
  newString.reserve(source.length()); // avoids a few memory allocations

  std::string::size_type lastPos = 0;
  std::string::size_type findPos;

  while (std::string::npos != (findPos = source.find(from, lastPos))) {
    newString.append(source, lastPos, findPos - lastPos);
    newString += to;
    lastPos = findPos + from.length();
  }

  // Care for the rest after last occurrence
  newString += source.substr(lastPos);

  source.swap(newString);
}
