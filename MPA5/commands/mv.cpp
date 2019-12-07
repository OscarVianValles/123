#include "mv.hpp"

mv::mv(std::list<std::string> inputParams) { params = inputParams; }

mv::~mv() {}

bool mv::execute(FileTree &t) {
  // Handle trivial test cases
  if (params.empty()) {
    std::cout << "mv: missing file operand" << std::endl;
    return false;
  } else if (params.size() == 1) {
    std::cout << "mv: missing destination file operand after '" +
                     params.front() + "'"
              << std::endl;

    return false;
  } else if (params.size() > 2) {
    std::cout << "mv: expected 2 arguments, got " << params.size() << std::endl;
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
    std::cout << "mv: cannot move '" + params.front() + "' to '" +
                     params.back() + "': no such file or directory"
              << std::endl;
    return false;
  }

  // Find if dist folder is available
  Node *distFolder;
  if (distTokens.back() == "") {
    distTokens.pop_back();
  }
  distFolder = t.search(distTokens, false);

  // if distFolder is not found, check if the the folder before the last path is
  // a folder
  if (!distFolder) {
    // Get possible name from tokens then remove the last token
    std::string name = distTokens.back();
    distTokens.pop_back();

    // If tokens still remain search for it, else change the dist folder to the
    // current working directory
    if (distTokens.size() >= 1) {
      distFolder = t.search(distTokens, false);

      // Handle if still it is still cannot be found
      if (!distFolder) {
        std::cout << "mv: cannot move '" + params.front() + "' to '" +
                         params.back() + "': no such file or directory"
                  << std::endl;
        return false;
      }
    } else {
      distFolder = t.current();
    }

    // Rename file
    currentFile->content.changeName(name);
  }

  currentFile->parent->dangerousRemoveChild(currentFile);
  distFolder->addChild(currentFile);
  return true;
}

bool mv::execute(FileTree &t, std::ofstream &output) {
  // Handle trivial test cases
  if (params.empty()) {
    output << "mv: missing file operand" << std::endl;
    return false;
  } else if (params.size() == 1) {
    output << "mv: missing destination file operand after '" + params.front() +
                  "'"
           << std::endl;

    return false;
  } else if (params.size() > 2) {
    output << "mv: expected 2 arguments, got " << params.size() << std::endl;
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
    output << "mv: cannot move '" + params.front() + "' to '" + params.back() +
                  "': no such file or directory"
           << std::endl;
    return false;
  }

  // Find if dist folder is available
  Node *distFolder;
  if (distTokens.back() == "") {
    distTokens.pop_back();
  }
  distFolder = t.search(distTokens, false);

  // if distFolder is not found, check if the the folder before the last path is
  // a folder
  if (!distFolder) {
    // Get possible name from tokens then remove the last token
    std::string name = distTokens.back();
    distTokens.pop_back();

    // If tokens still remain search for it, else change the dist folder to the
    // current working directory
    if (distTokens.size() >= 1) {
      distFolder = t.search(distTokens, false);

      // Handle if still it is still cannot be found
      if (!distFolder) {
        output << "mv: cannot move '" + params.front() + "' to '" +
                      params.back() + "': no such file or directory"
               << std::endl;
        return false;
      }
    } else {
      distFolder = t.current();
    }

    // Rename file
    currentFile->content.changeName(name);
  }

  currentFile->parent->dangerousRemoveChild(currentFile);
  distFolder->addChild(currentFile);
  return true;
}
