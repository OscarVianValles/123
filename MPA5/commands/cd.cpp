#include "cd.hpp"

cd::cd(std::list<std::string> inputParams) { params = inputParams; }

cd::~cd() {}

bool cd::execute(FileTree &t) {
  // Check for trivial test cases
  if (params.empty()) {
    std::cout << "cd: missing file operand" << std::endl;
    return false;
  }

  // Get the arguments
  std::string inputString = params.front();

  if (inputString == "..") {
    // If parent exists go to parent
    if (t.current()->parent != nullptr) {
      t.changeCurrent(t.current()->parent);
    }
  } else {
    // Search for the node using strings
    Node *testNode = t.search(inputString, false);

    // If node exists, go to node
    if (testNode) {
      t.changeCurrent(testNode);
    }
  }

  return true;
}

bool cd::execute(FileTree &t, std::ofstream output) {
  // Check for trivial test cases
  if (params.empty()) {
    std::cout << "cd: missing file operand" << std::endl;
    return false;
  }

  // Get the arguments
  std::string inputString = params.front();

  if (inputString == "..") {
    // If parent exists go to parent
    if (t.current()->parent != nullptr) {
      t.changeCurrent(t.current()->parent);
    }
  } else {
    // Search for the node using strings
    Node *testNode = t.search(inputString, false);

    // If node exists, go to node
    if (testNode) {
      t.changeCurrent(testNode);
    }
  }

  return true;
}
