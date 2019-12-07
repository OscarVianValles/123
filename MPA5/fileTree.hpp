#ifndef MPA5_FILETREE
#define MPA5_FILETREE

#include "helpers.hpp"
#include "node.hpp"
#include <stack>
class FileTree {
private:
  Node *__root, *__current;
  Node *__search(Node *, std::string, std::list<std::string>, bool);

public:
  FileTree();
  ~FileTree();

  Node *search(std::string, bool);
  Node *search(std::list<std::string>, bool);

  std::stack<Node *> whereis(std::string);

  Node *root();
  Node *current();

  bool insert(Node *);
  bool insert(Node *, Node *);

  bool remove(Node *);
  void changeCurrent(Node *);

  std::string nodePath(Node *);
};
#endif
