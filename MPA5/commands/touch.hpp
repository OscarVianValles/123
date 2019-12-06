#ifndef MPA5_TOUCH
#define MPA5_TOUCH

#include "append.hpp"
#include "command.hpp"
#include <iostream>
#include <list>
#include <string>

class touch : public Command {
public:
  touch(std::list<std::string>);
  ~touch();
  bool execute(FileTree &);
};

#endif
