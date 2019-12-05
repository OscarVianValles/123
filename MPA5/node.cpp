#include "node.hpp"

// Constructors
Node::Node(bool isFile, std::string fileName) : content(isFile, fileName) {}

Node::Node(bool isFile, std::string fileName, std::string fileContent)
    : content(isFile, fileName, fileContent) {}

// Recursively deletes the content of the node. This will call the first
// child, will remove it from the list, then call this destructor again, which
// will properly delete all contents of the tree
Node::~Node() {
  while (!children.empty()) {
    removeChild(children.front());
  }
}

// Append files at the back, push directories at the front
bool Node::addChild(Node *x) {
  // Prevents adding children to nodes that are files
  if (content.isFile()) {
    return false;
  } else {
    x->parent = this;
    if (x->content.isFile()) {
      children.push_back(x);
    } else {
      children.push_front(x);
    }
    return true;
  }
}

// Deletes the node from the list, then properly deallocates the node
bool Node::removeChild(Node *x) {
  // Prevents running the function if the node is a file
  if (content.isFile()) {
    return false;
  } else {
    auto i = children.begin();
    auto end = children.end();
    while (i != end) {
      if (*(i) == x) {
        i = children.erase(i);
        delete x;
        return true;
      } else {
        ++i;
      }
    }
  }

  return false;
}
