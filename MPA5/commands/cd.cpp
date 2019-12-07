#include "cd.hpp"

cd::cd(std::list<std::string> inputParams) { params = inputParams; }

cd::~cd() {}

bool cd::execute(FileTree &t) {
  // Check for trivial test cases
  if (params.empty()) {
    std::cout
        << "usage: cp source_file/source_directory target_file/target_directory"
        << std::endl;
    return false;
  }

  // Get the arguments
  std::string inputString = params.front();

  // Search for the node using strings
  Node *testNode = t.search(inputString, false);

  if (testNode) {
    t.changeCurrent(testNode);
  } else {
    std::cout << "cd: " + params.front() + ": No such file or directory"
              << std::endl;
  }

  return true;
}

bool cd::execute(FileTree &t, std::ofstream &output) {
  // Check for trivial test cases
  if (params.empty()) {
    std::cout
        << "usage: cp source_file/source_directory target_file/target_directory"
        << std::endl;
    return false;
  }

  // Get the arguments
  std::string inputString = params.front();

  // Search for the node using strings
  Node *testNode = t.search(inputString, false);

  // If node exists, go to node
  if (testNode) {
    t.changeCurrent(testNode);
  } else {
    output << "cd: " + params.front() + ": No such file or directory"
           << std::endl;
  }

  return true;
}
