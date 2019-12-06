#include "ls.hpp"

ls::ls(std::list<std::string> inputParams) { params = inputParams; }

ls::~ls() {}

bool ls::execute(FileTree &t) {
  if (params.empty()) {
    Node *curr = t.current();
    for (auto &child : curr->children) {
      std::cout << child->content.name()
                << (child->content.isFolder() ? "/" : "") << std::endl;
    }
    return true;
  }
}
