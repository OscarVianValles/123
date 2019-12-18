#include "whereis.hpp"

whereis::whereis(std::list<std::string> inputParams) { params = inputParams; }

whereis::~whereis() {}

bool whereis::execute(FileTree &t) {
  // Handle trivial test cases
  if (params.empty()) {
    std::cout << "whereis: not enough arguments" << std::endl;
    return false;
  }

  std::stack<Node *> nodes = t.whereis(params.front());
  while (!nodes.empty()) {
    std::cout << t.nodePath(nodes.top()) << std::endl;
    nodes.pop();
  }

  return true;
}

bool whereis::execute(FileTree &t, std::ofstream &output) {
  // Handle trivial test cases
  if (params.empty()) {
    output << "whereis: not enough arguments" << std::endl;
    return false;
  }

  std::stack<Node *> nodes = t.whereis(params.front());
  while (!nodes.empty()) {
    output << t.nodePath(nodes.top()) << std::endl;
    nodes.pop();
  }

  return true;
}
