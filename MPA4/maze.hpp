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
  Maze();
  Maze(std::string, int, int);
  Maze(std::string, Coordinates);
  Maze(const Maze &);
  ~Maze();

  void visit(Coordinates);
  void close(Coordinates);

  Coordinates dimensions() const;
  std::string stringRepresentation(bool) const;
  Coordinates source() const;
  Cell at(Coordinates) const;
};

#endif
