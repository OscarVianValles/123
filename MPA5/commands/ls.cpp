#include "ls.hpp"

ls::ls(std::list<std::string> inputParams) { params = inputParams; }

ls::~ls() {}

bool ls::execute(FileTree &t) {
  if (params.empty()) {
    Node *curr = t.current();
    __printDirectory(curr);
    return true;
  } else {
    std::list<std::string> tokens = tokenize(params.front(), '/');
    if (tokens.back() == "") {
      tokens.pop_back();
    }

    // Try searching for directory
    Node *currNode = t.search(tokens, false);
    if (currNode) {
      __printDirectory(currNode);
    } else {
      // If currNode was not found, then try if the last string is a valid
      // regex, if it is not valid, then it returns an error
      std::regex pattern(".*");
      try {
        std::string possibleRegex = tokens.back();
        if (possibleRegex[0] == '*' && possibleRegex[1] == '.') {
          possibleRegex = "." + possibleRegex + "$";
        }

      } catch (std::regex_error &e) {
        std::cout << "ls: cannot access '" + params.front() +
                         "': No such file or directory"
                  << std::endl;
        return false;
      }

      tokens.pop_back();
      Node *currNode = t.current();
      if (tokens.size() >= 1) {
        currNode = t.search(tokens, false);

        if (!currNode) {
          std::cout << "ls: cannot access '" + params.front() +
                           "': No such file or directory"
                    << std::endl;
          return false;
        }
      }

      __printDirectory(currNode, pattern);
    }
  }

  return true;
}

void ls::__printDirectory(Node *curr) {
  for (auto &child : curr->children) {
    std::cout << child->content.name() << (child->content.isFolder() ? "/" : "")
              << std::endl;
  }
}

void ls::__printDirectory(Node *curr, std::regex pattern) {
  for (auto &child : curr->children) {
    if (std::regex_match(child->content.name(), pattern)) {
      std::cout << child->content.name()
                << (child->content.isFolder() ? "/" : "") << std::endl;
    }
  }
}
