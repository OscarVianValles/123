#ifndef MPA5_RM
#define MPA5_RM

#include "command.hpp"
#include <iostream>
#include <list>
#include <string>

class rm : public Command {
public:
  rm(std::list<std::string>);
  ~rm();
  bool execute(FileTree &);
  bool execute(FileTree &, std::ofstream &);
};

#endif
