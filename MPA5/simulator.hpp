#ifndef MPA5_SIMULATOR
#define MPA5_SIMULATOR

#include "commands.hpp"
#include "fileTree.hpp"
#include "helpers.hpp"
#include <fstream>
#include <iostream>

class Simulator {
private:
  FileTree *t;
  void __readFile();
  void __writeFile();

public:
  Simulator();
  ~Simulator();
  void execute();
  void executeFromFile();
};

#endif
