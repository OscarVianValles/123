#include "commands.hpp"
#include "fileTree.hpp"

int main() {
  FileTree *a = new FileTree();
  Node *file = new Node(true, "file");

  a->root()->addChild(file);
  std::list<std::string> params;
  params.push_back("test");
  Command *c = new mkdir(params);
  c->execute(*a);

  Command *s = new ls(params);
  s->execute(*a);
  delete c;
  delete s;
  delete a;
}
