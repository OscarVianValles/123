#ifndef MPA5_COMMAND
#define MPA5_COMMAND

#include "../fileTree.hpp"
#include "../node.hpp"
#include <list>
#include <string>

class Command {
protected:
  std::list<std::string> params;

public:
  virtual ~Command(){};
  virtual bool execute(FileTree &) = 0;
};

#endif
