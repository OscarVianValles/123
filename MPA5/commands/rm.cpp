#include "rm.hpp"

rm::rm(std::list<std::string> inputParams) { params = inputParams; }

rm::~rm() {}

bool rm::execute(FileTree &t) {
  // Handle trivial test cases
  if (params.empty()) {
    std::cout << "rm: missing file operand" << std::endl;
    return false;
  }

  // Search for file
  Node *currentFile = t.search(params.front(), true);

  // If file is found, show file, else throw error message
  if (currentFile) {
    t.remove(currentFile);
  } else {
    std::cout << "rm: file not found" << std::endl;
    return false;
  }
  return true;
}

bool rm::execute(FileTree &t, std::ofstream &output) {
  // Handle trivial test cases
  if (params.empty()) {
    output << "rm: missing file operand" << std::endl;
    return false;
  }

  // Search for file
  Node *currentFile = t.search(params.front(), true);

  // If file is found, show file, else throw error message
  if (currentFile) {
    t.remove(currentFile);
  } else {
    output << "rm: file not found" << std::endl;
    return false;
  }
  return true;
}
