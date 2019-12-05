#include "ls.hpp"

ls::ls(std::list<std::string> inputParams) { params = inputParams; }

ls::~ls() {}
bool ls::execute(FileTree &t) {

  Node *curr = t.current();
  for (auto &child : curr->children) {
    std::cout << child->content.name() << std::endl;
  }

  return true;
}
