#include "cp.hpp"

cp::cp(std::list<std::string> inputParams) { params = inputParams; }

cp::~cp() {}

bool cp::execute(FileTree &t) {
  // Handle trivial test cases
  if (params.empty()) {
    std::cout
        << "usage: cp source_file/source_directory target_file/target_directory"
        << std::endl;
    return false;
  } else if (params.size() == 1) {
    std::cout << "cp: missing destination file operand after '" +
                     params.front() + "'"
              << std::endl;

    return false;
  } else if (params.size() > 2) {
    std::cout << "cp: expected 2 arguments, got " << params.size() << std::endl;
    return false;
  }

  // Tokenize source and dist arguments
  std::list<std::string> sourceTokens = tokenize(params.front(), '/');
  std::list<std::string> distTokens = tokenize(params.back(), '/');

  // Get current file
  Node *currentFile;
  // try searching for folder
  currentFile = t.search(sourceTokens, false);
  if (!currentFile) {
    currentFile = t.search(sourceTokens, true);
  }

  // Handle if file is not found
  if (!currentFile) {
    std::cout << "cp: cannot stat '" + sourceTokens.back() +
                     "': No such file or directory"
              << std::endl;
    return false;
  }

  // Handle if "cp foo/ bar/baz/", i.e. if the last location has an extra /, if
  // the copied file is a directory"
  if (distTokens.back() == "") {
    if (currentFile->content.isFolder()) {
      distTokens.pop_back();
    } else {
      std::cout << "cp: expected new name for file, got directory instead"
                << std::endl;
      return false;
    }
  }

  // Create new file
  // Remove name from tokens
  std::string newName = distTokens.back();
  distTokens.pop_back();

  // Create new node and rename file
  Node *newNode = new Node(*currentFile);
  newNode->content.changeName(newName);

  // If token size is greater than 1, then a directory was passed as an
  // argument. The directory is searched for, then the node is inserted there,
  // else insert it at the current node
  if (distTokens.size() >= 1) {
    Node *fileLocation = t.search(distTokens, false);

    if (fileLocation) {
      t.insert(fileLocation, newNode);
      return true;
    } else {
      std::cout << "cp: cannot create regular file '" + params.back() +
                       "': No such file or directory"
                << std::endl;
      return false;
    }
  } else {
    t.insert(newNode);
    return true;
  }
}

bool cp::execute(FileTree &t, std::ofstream &output) {
  // Handle trivial test cases
  if (params.empty()) {
    output
        << "usage: cp source_file/source_directory target_file/target_directory"
        << std::endl;
    return false;
  } else if (params.size() == 1) {
    output << "cp: missing destination file operand after '" + params.front() +
                  "'"
           << std::endl;

    return false;
  } else if (params.size() > 2) {
    output << "cp: expected 2 arguments, got " << params.size() << std::endl;
    return false;
  }

  // Tokenize source and dist arguments
  std::list<std::string> sourceTokens = tokenize(params.front(), '/');
  std::list<std::string> distTokens = tokenize(params.back(), '/');

  // Get current file
  Node *currentFile;
  // try searching for folder
  currentFile = t.search(sourceTokens, false);
  if (!currentFile) {
    currentFile = t.search(sourceTokens, true);
  }

  // Handle if file is not found
  if (!currentFile) {
    output << "cp: cannot stat '" + sourceTokens.back() +
                  "': No such file or directory"
           << std::endl;
    return false;
  }

  // Handle if "cp foo/ bar/baz/", i.e. if the last location has an extra /, if
  // the copied file is a directory"
  if (distTokens.back() == "") {
    if (currentFile->content.isFolder()) {
      distTokens.pop_back();
    } else {
      output << "cp: expected new name for file, got directory instead"
             << std::endl;
      return false;
    }
  }

  // Create new file
  // Remove name from tokens
  std::string newName = distTokens.back();
  distTokens.pop_back();

  // Create new node and rename file
  Node *newNode = new Node(*currentFile);
  newNode->content.changeName(newName);

  // If token size is greater than 1, then a directory was passed as an
  // argument. The directory is searched for, then the node is inserted there,
  // else insert it at the current node
  if (distTokens.size() >= 1) {
    Node *fileLocation = t.search(distTokens, false);

    if (fileLocation) {
      t.insert(fileLocation, newNode);
      return true;
    } else {
      output << "cp: cannot create regular file '" + params.back() +
                    "': No such file or directory"
             << std::endl;
      return false;
    }
  } else {
    t.insert(newNode);
    return true;
  }
}
