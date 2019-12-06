
#include "touch.hpp"

touch::touch(std::list<std::string> inputParams) { params = inputParams; }

touch::~touch() {}

bool touch::execute(FileTree &t) {
  if (params.empty()) {
    std::cout << "touch: missing file operand" << std::endl;
    return false;
  }

  Node *currentFile = t.search(params.front());
  if (currentFile) {
    currentFile->content.emptyFileContent();
  } else {
    Node *newFile = new Node(true, params.front());
    t.insert(newFile);
  }
  return true;
}
