#include "show.hpp"

show::show(std::list<std::string> inputParams) { params = inputParams; }

show::~show() {}

bool show::execute(FileTree &t) {
  // Handle trivial test cases
  if (params.empty()) {
    std::cout << "show: missing file operand" << std::endl;
    return false;
  }

  // Search for file
  Node *currentFile = t.search(params.front(), true);

  // If file is found, show file, else throw error message
  if (currentFile) {
    std::cout << currentFile->content.fileContent() << std::endl;
  } else {
    std::cout << "show: file not found" << std::endl;
    return false;
  }

  return true;
}

bool show::execute(FileTree &t, std::ofstream &output) {
  // Handle trivial test cases
  if (params.empty()) {
    output << "show: missing file operand" << std::endl;
    return false;
  }

  // Search for file
  Node *currentFile = t.search(params.front(), true);

  // If file is found, show file, else throw error message
  if (currentFile) {
    output << currentFile->content.fileContent() << std::endl;
  } else {
    output << "show: file not found" << std::endl;
    return false;
  }

  return true;
}
