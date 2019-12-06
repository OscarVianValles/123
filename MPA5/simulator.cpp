#include "simulator.hpp"

std::string Simulator::currentPath() {
  Node *curr = t->current();
  std::string path;
  while (curr) {
    path.insert(0, "/" + curr->content.name());
  }

  return path;
}

Simulator::Simulator() { t = new FileTree(); }

Simulator::~Simulator() { delete t; }

void Simulator::execute() {
  while (true) {
    std::string inputString;
    std::cin >> inputString;
    std::list<std::string> tokens = tokenize(inputString, ' ');
  }
}
