#include "rn.hpp"

rn::rn(std::list<std::string> inputParams) { params = inputParams; }

rn::~rn() {}
bool rn::execute(FileTree &t) {
  // Handle trivial test cases
  if (params.empty()) {
    std::cout << "rn: missing file operand" << std::endl;
    return false;
  } else if (params.size() == 1) {
    std::cout << "rn: missing destination file operand after '" +
                     params.front() + "'"
              << std::endl;

    return false;
  } else if (params.size() > 2) {
    std::cout << "rn: expected 2 arguments, got " << params.size() << std::endl;
    return false;
  }

  // Search for file
  Node *currentFile = t.search(params.front(), true);

  // If file is found, rename file, else throw error message
  if (currentFile) {
    currentFile->content.changeName(params.back());
  } else {
    std::cout << "rn: file not found" << std::endl;
    return false;
  }

  return true;
}

bool rn::execute(FileTree &t, std::ofstream &output) {
  // Handle trivial test cases
  if (params.empty()) {
    output << "rn: missing file operand" << std::endl;
    return false;
  } else if (params.size() == 1) {
    output << "rn: missing destination file operand after '" + params.front() +
                  "'"
           << std::endl;

    return false;
  } else if (params.size() > 2) {
    output << "rn: expected 2 arguments, got " << params.size() << std::endl;
    return false;
  }

  // Search for file
  Node *currentFile = t.search(params.front(), true);

  // If file is found, rename file, else throw error message
  if (currentFile) {
    currentFile->content.changeName(params.back());
  } else {
    output << "rn: file not found" << std::endl;
    return false;
  }

  return true;
}
