#include "node.hpp"

bool nodeCompare(Node *first, Node *second) {
  return first->content.name() < second->content.name();
}

// Constructors
Node::Node(bool isFile, std::string fileName) : content(isFile, fileName) {
  parent = nullptr;
}

Node::Node(bool isFile, std::string fileName, std::string fileContent)
    : content(isFile, fileName, fileContent) {
  parent = nullptr;
}

// Recursively copies the content of the node
Node::Node(const Node &original) : content(original.content) {
  parent = nullptr;
  for (auto &child : original.children) {
    Node *newNode = new Node((*child));
    addChild(newNode);
  }
}

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

    children.sort(nodeCompare);
    return true;
  }
}

// Deletes the node from the list, then properly deallocates the node
bool Node::removeChild(Node *x) {
  // Prevents running the function if the current node is a file since a file
  // should have no children
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

// Deletes the node from the list BUT DOES NOT DEALLOCATES IT
bool Node::dangerousRemoveChild(Node *x) {
  // Prevents running the function if the current node is a file since a file
  // should have no children
  if (content.isFile()) {
    return false;
  } else {
    auto i = children.begin();
    auto end = children.end();
    while (i != end) {
      if (*(i) == x) {
        i = children.erase(i);
        return true;
      } else {
        ++i;
      }
    }
  }

  return false;
}
