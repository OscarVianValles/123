#ifndef MPA4_MAZE
#define MPA4_MAZE

#include "cell.hpp"
#include "coordinates.hpp"
#include <string>

class Maze {
private:
  Cell **__maze;
  Coordinates __dimensions;

  void __tokenize(std::string);
  void __allocateMem();

public:
  Maze(std::string, int, int);
  Maze(std::string, Coordinates);
  ~Maze();
  std::string stringRepresentation();
};

#endif
