#include "fileTree.hpp"
#include <iostream>

// Constructor
FileTree::FileTree() {
  __root = new Node(false, "");
  __current = __root;
}

// Deconstructor. Deleting root will recursively delete its children
FileTree::~FileTree() { delete __root; }

// Recursively searches through all of the children depending on the string
Node *FileTree::search(std::string x, bool isFile) {
  // Tokenize input string
  std::list<std::string> tokens = tokenize(x, '/');

  // Get first element of the string to check if the first character was "/"
  // which indicates that it is searching from the root
  std::string initial = tokens.front();
  if (initial == "") {
    tokens.pop_front();
    return __search(__root, initial, tokens, isFile);
  } else {
    return __search(__current, __current->content.name(), tokens, isFile);
  }
}

Node *FileTree::search(std::list<std::string> tokens, bool isFile) {
  // Get first element of the string to check if the first character was "/"
  // which indicates that it is searching from the root
  std::string initial = tokens.front();
  if (initial == "") {
    tokens.pop_front();
    return __search(__root, initial, tokens, isFile);
  } else {
    return __search(__current, __current->content.name(), tokens, isFile);
  }
}

// Recursive Search
Node *FileTree::__search(Node *current, std::string searchItem,
                         std::list<std::string> tokens, bool isFile) {

  if (current->content.name() == searchItem) {
    // If tokens is empty, then that means that the last folder has been
    // reached. If not, then search the next child
    if (tokens.empty()) {
      if (current->content.isFile() == isFile) {
        return current;
      } else {
        return nullptr;
      }
    } else {
      // Get new search item
      std::string newSearchItem = tokens.front();
      tokens.pop_front();
      Node *nextNode = current;

      while (newSearchItem == "..") {
        nextNode = nextNode->parent;
        if (!nextNode) {
          return nullptr;
        }
        if (tokens.size() >= 1) {
          newSearchItem = tokens.front();
          tokens.pop_front();
        } else {
          return nextNode;
        }
      }

      Node *returnValue;
      // Searching for new search item in each children
      for (auto &child : nextNode->children) {
        returnValue = __search(child, newSearchItem, tokens, isFile);
        if (returnValue != nullptr) {
          return returnValue;
        }
      }
    }
  }

  return nullptr;
}

std::stack<Node *> FileTree::whereis(std::string fileName) {
  std::stack<Node *> nodes;
  std::stack<Node *> foundNodes;
  nodes.push(__current);
  while (!nodes.empty()) {
    Node *curr = nodes.top();
    nodes.pop();
    for (auto &child : curr->children) {
      nodes.push(child);
    }
    if (curr->content.name() == fileName) {
      foundNodes.push(curr);
    }
  }

  return foundNodes;
}

Node *FileTree::root() { return __root; }

Node *FileTree::current() { return __current; }

bool FileTree::insert(Node *x) { return insert(__current, x); }

bool FileTree::insert(Node *to, Node *x) { return to->addChild(x); }

bool FileTree::remove(Node *x) {
  if (x) {
    Node *to = x->parent;
    if (x == __root) {
      return false;
    } else if (x == __current) {
      __current = __current->parent;
    }

    return to->removeChild(x);
  } else {
    return false;
  }
}

void FileTree::changeCurrent(Node *x) { __current = x; }

std::string FileTree::nodePath(Node *x) {
  Node *curr = x;
  std::string path;
  while (curr) {
    path.insert(0, curr->content.name() + "/");
    curr = curr->parent;
  }

  return path;
}
