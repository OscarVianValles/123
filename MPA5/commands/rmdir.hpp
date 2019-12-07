#ifndef MPA5_RMDIR
#define MPA5_RMDIR

#include "command.hpp"
#include <iostream>
#include <list>
#include <string>

class rmdir : public Command {
public:
  rmdir(std::list<std::string>);
  ~rmdir();
  bool execute(FileTree &);
  bool execute(FileTree &, std::ofstream);
};

#endif
