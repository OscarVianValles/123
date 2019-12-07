#ifndef MPA5_LS
#define MPA5_LS

#include "command.hpp"
#include <iostream>
#include <list>
#include <regex>
#include <string>

class ls : public Command {
private:
  void __printDirectory(Node *, std::regex);
  void __printDirectory(Node *);

public:
  ls(std::list<std::string>);
  ~ls();
  bool execute(FileTree &);
};

#endif
