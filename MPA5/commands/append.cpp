#include "append.hpp"

append::append(std::list<std::string> inputParams) { params = inputParams; }

append::~append() {}

bool append::execute(FileTree &t) {
  // Trivial test cases first
  if (params.empty()) {
    std::cout << "append: missing file operand" << std::endl;
    return false;
  }

  // Search for file
  Node *currNode = t.search(params.front(), true);

  // If node is not found, create file
  if (!currNode) {
    touch c(params);
    c.execute(t);
    return true;
  }

  // Print file contents
  std::cout << currNode->content.fileContent();

  // create temporary strings
  std::string tempHolder;
  std::string newFileContent;

  // Get file content from user
  while (true) {
    std::getline(std::cin, tempHolder);

    // If :w is found, stop reading
    if (tempHolder == ":w") {
      break;
    }

    // if empty, do not place leading new line.
    if (newFileContent.empty()) {
      newFileContent = tempHolder;
    } else {
      newFileContent += "\n" + tempHolder;
    }
  }

  // Appends content to file
  currNode->content.appendFileContent(newFileContent);
  return true;
}
