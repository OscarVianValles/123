#ifndef MPA5_CP
#define MPA5_CP

#include "command.hpp"
#include <iostream>
#include <list>
#include <string>

class cp : public Command {
public:
  cp(std::list<std::string>);
  ~cp();
  bool execute(FileTree &);
};

#endif
