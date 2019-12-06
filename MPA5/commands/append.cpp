#include "append.hpp"

append::append(std::list<std::string> inputParams) { params = inputParams; }

append::~append() {}

bool append::execute(FileTree &t) {
  if (params.empty()) {
    std::cout << "append: missing file operand" << std::endl;
    return false;
  }
  Node *currNode = t.search(params.front(), true);

  if (!currNode) {
    std::cout << "WIP" << std::endl;
    return false;
  }

  std::cout << currNode->content.fileContent();

  std::string tempHolder;
  std::string newFileContent;

  while (true) {

    std::getline(std::cin, tempHolder);
    if (tempHolder == ":w" || (!newFileContent.empty() && tempHolder == "")) {
      break;
    }
    if (newFileContent.empty()) {
      newFileContent = tempHolder;
    }
    newFileContent += "\n" + tempHolder;
  }

  currNode->content.appendFileContent(newFileContent);
  return true;
}
