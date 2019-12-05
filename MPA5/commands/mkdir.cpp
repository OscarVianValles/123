#include "mkdir.hpp"

mkdir::mkdir(std::list<std::string> inputParams) { params = inputParams; }

mkdir::~mkdir() {}

bool mkdir::execute(FileTree &t) {
  Node *curr = t.current();
  Node *newNode = new Node(false, params.front());
  curr->addChild(newNode);
  return true;
}
