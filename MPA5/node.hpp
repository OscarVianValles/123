#ifndef MPA5_NODE
#define MPA5_NODE

#include "fileDescriptor.hpp"
#include <algorithm>
#include <list>
class Node {
public:
  Descriptor content;
  Node *parent;
  std::list<Node *> children;

  Node(bool, std::string);
  Node(bool, std::string, std::string);
  Node(const Node &);

  ~Node();

  bool addChild(Node *);
  bool removeChild(Node *);
  bool dangerousRemoveChild(Node *);
};
#endif
