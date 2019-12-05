#ifndef MPA5_CD
#define MPA5_CD

#include "command.hpp"
#include <iostream>
#include <list>
#include <string>

class cd : public Command {
public:
  cd(std::list<std::string>);
  ~cd();
  bool execute(FileTree &);
};

#endif
