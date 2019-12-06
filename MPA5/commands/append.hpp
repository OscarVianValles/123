#ifndef MPA5_APPEND
#define MPA5_APPEND

#include "command.hpp"
#include "touch.hpp"
#include <iostream>
#include <list>
#include <string>

class append : public Command {
public:
  append(std::list<std::string>);
  ~append();
  bool execute(FileTree &);
};

#endif
