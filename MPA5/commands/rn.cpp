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
  }

  Node *currentFile = t.search(params.front(), true);
  if (currentFile) {
    currentFile->content.changeName(params.back());
  } else {
    std::cout << "rn: file not found" << std::endl;
    return false;
  }

  return true;
}
