#ifndef MPA5_NODE
#define MPA5_NODE

#include "fileDescriptor.hpp"
#include <list>
class Node {
public:
  int a;
  Descriptor content;
  std::list<Node *> children;

  Node(bool, std::string);
  Node(bool, std::string, std::string);

  ~Node();

  bool addChild(Node *);
  bool removeChild(Node *);
};

#endif
