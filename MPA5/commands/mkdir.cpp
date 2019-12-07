#include "mkdir.hpp"

mkdir::mkdir(std::list<std::string> inputParams) { params = inputParams; }

mkdir::~mkdir() {}

bool mkdir::execute(FileTree &t) {
  // Trivial test cases first
  if (params.empty()) {
    std::cout << "mkdir: directory name cannot be blank" << std::endl;
    return false;
  }

  // Tokenize list
  std::list<std::string> tokens = tokenize(params.front(), '/');

  // Get current node
  Node *curr = t.current();

  // Handle if "mkdir /test/test/"
  if (tokens.back() == "") {
    tokens.pop_back();
  }

  // Get name of folder. This is always the last token
  std::string name = tokens.back();
  tokens.pop_back();

  // If more than one token remain, then this is a path, go to the path
  if (tokens.size() >= 1) {
    curr = t.search(tokens, false);
  }

  // If path is not found, error message
  if (curr == nullptr) {
    std::cout << "mkdir: parent directory not found" << std::endl;
    return false;
  }

  // Create node and add it as a child
  Node *newNode = new Node(false, name);
  curr->addChild(newNode);
  return true;
}

bool mkdir::execute(FileTree &t, std::ofstream output) {
  // Trivial test cases first
  if (params.empty()) {
    output << "mkdir: directory name cannot be blank" << std::endl;
    return false;
  }

  // Tokenize list
  std::list<std::string> tokens = tokenize(params.front(), '/');

  // Get current node
  Node *curr = t.current();

  // Handle if "mkdir /test/test/"
  if (tokens.back() == "") {
    tokens.pop_back();
  }

  // Get name of folder. This is always the last token
  std::string name = tokens.back();
  tokens.pop_back();

  // If more than one token remain, then this is a path, go to the path
  if (tokens.size() >= 1) {
    curr = t.search(tokens, false);
  }

  // If path is not found, error message
  if (curr == nullptr) {
    output << "mkdir: parent directory not found" << std::endl;
    return false;
  }

  // Create node and add it as a child
  Node *newNode = new Node(false, name);
  curr->addChild(newNode);
  return true;
}
