#ifndef MPA5_LS
#define MPA5_LS

#include "command.hpp"
#include <iostream>
#include <list>
#include <regex>
#include <string>

class ls : public Command {
private:
  void __printDirectoryFile(Node *, std::regex, std::ofstream &);
  void __printDirectoryFile(Node *, std::ofstream &);
  void __printDirectory(Node *, std::regex);
  void __printDirectory(Node *);

public:
  ls(std::list<std::string>);
  ~ls();
  bool execute(FileTree &);
  bool execute(FileTree &, std::ofstream &);
};

#endif
