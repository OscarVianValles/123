#ifndef MPA5_LS
#define MPA5_LS

#include "command.hpp"
#include <iostream>
#include <list>
#include <string>

class ls : public Command {
public:
  ls(std::list<std::string>);
  ~ls();
  bool execute(FileTree &);
};

#endif
