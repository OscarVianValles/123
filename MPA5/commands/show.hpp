#ifndef MPA5_SHOW
#define MPA5_SHOW

#include "command.hpp"
#include <iostream>
#include <list>
#include <string>

class show : public Command {
public:
  show(std::list<std::string>);
  ~show();
  bool execute(FileTree &);
  bool execute(FileTree &, std::ofstream &);
};

#endif
