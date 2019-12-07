#include "rmdir.hpp"

rmdir::rmdir(std::list<std::string> inputParams) { params = inputParams; }

rmdir::~rmdir() {}

bool rmdir::execute(FileTree &t) {
  if (params.empty()) {
    std::cout << "rmdir: missing operand" << std::endl;
    return false;
  }

  std::list<std::string> tokens = tokenize(params.front(), '/');

  if (tokens.back() == "") {
    tokens.pop_back();
  }

  Node *curr = t.search(tokens, false);

  if (curr == nullptr) {
    std::cout << "rmdir: no such directory" << std::endl;
    return false;
  }

  t.remove(curr);
  return true;
}

bool rmdir::execute(FileTree &t, std::ofstream &output) {
  if (params.empty()) {
    output << "rmdir: missing operand" << std::endl;
    return false;
  }

  std::list<std::string> tokens = tokenize(params.front(), '/');

  if (tokens.back() == "") {
    tokens.pop_back();
  }

  Node *curr = t.search(tokens, false);

  if (curr == nullptr) {
    output << "rmdir: no such directory" << std::endl;
    return false;
  }

  t.remove(curr);
  return true;
}
