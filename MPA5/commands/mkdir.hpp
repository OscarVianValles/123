#ifndef MPA5_MKDIR
#define MPA5_MKDIR

#include "command.hpp"
#include <iostream>
#include <list>
#include <string>
class mkdir : public Command {
public:
  mkdir(std::list<std::string>);
  ~mkdir();
  bool execute(FileTree &);
};

#endif
