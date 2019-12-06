
#include "touch.hpp"

touch::touch(std::list<std::string> inputParams) { params = inputParams; }

touch::~touch() {}

bool touch::execute(FileTree &t) {
  if (params.empty()) {
    std::cout << "touch: missing file operand" << std::endl;
    return false;
  }

  Node *currentFile = t.search(params.front(), true);
  if (currentFile) {
    currentFile->content.emptyFileContent();
  } else {
    std::list<std::string> tokens = tokenize(params.front(), '/');
    std::string name = tokens.back();
    tokens.pop_back();

    Node *newFile = new Node(true, name);
    if (tokens.size() >= 1) {
      Node *currDir = t.search(tokens, false);
      if (!currDir) {
        std::cout << "touch: parent directory not found" << std::endl;
        return false;
      } else {
        t.insert(currDir, newFile);
      }
    } else {
      t.insert(newFile);
    }
  }

  append a(params);
  a.execute(t);
  return true;
}
