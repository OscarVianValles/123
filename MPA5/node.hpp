#ifndef MPA5_NODE
#define MPA5_NODE

#include "fileDescriptor.hpp"
#include <list>
class Node {
public:
  Descriptor d;
  std::list<Node *> children;

  Node(bool, std::string);
  Node(bool, std::string, std::string);
};

#endif
