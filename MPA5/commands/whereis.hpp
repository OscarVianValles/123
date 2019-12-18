#ifndef MPA5_WHEREIS
#define MPA5_WHEREIS

#include "command.hpp"
#include <iostream>
#include <list>
#include <string>

class whereis : public Command {
public:
  whereis(std::list<std::string>);
  ~whereis();
  bool execute(FileTree &);
  bool execute(FileTree &, std::ofstream &);
};

#endif
