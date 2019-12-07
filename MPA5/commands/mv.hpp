#ifndef MPA5_MV
#define MPA5_MV

#include "command.hpp"
#include <iostream>
#include <list>
#include <string>

class mv : public Command {
public:
  mv(std::list<std::string>);
  ~mv();
  bool execute(FileTree &);
  bool execute(FileTree &, std::ofstream);
};

#endif
