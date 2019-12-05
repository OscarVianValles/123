#include "fileTree.hpp"

int main() {
  FileTree *a = new FileTree();
  Node *b = new Node(true, "asd");
  Node *d = new Node(true, "adsf");
  Node *e = new Node(true, "was");
  a->root();
  std::list<std::string> params;
  Command *c = new ls(params);
  a->insert(b);
  a->insert(d);
  a->insert(e);
  a->execute(c);
  delete c;
  delete a;
}
