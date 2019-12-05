#ifndef MPA5_RN
#define MPA5_RN

#include "command.hpp"
#include <iostream>
#include <list>
#include <string>

class rn : public Command {
public:
  rn(std::list<std::string>);
  ~rn();
  bool execute(FileTree &);
};

#endif
