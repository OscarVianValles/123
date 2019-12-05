#ifndef MPA5_LS
#define MPA5_LS

#include "command.hpp"
#include <iostream>
class ls : public Command {
public:
  ls(std::list<std::string>);
  ~ls();
  bool execute(FileTree &);
};

#endif
