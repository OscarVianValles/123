#ifndef MPA4_MAZESOLVER
#define MPA4_MAZESOLVER

#include "agenda.hpp"
#include "coordinates.hpp"
#include "maze.hpp"
#include <stack>

template <class T> class MazeSolver {
private:
  Agenda<T> __a;
  Coordinates __currentLocation;
  Maze *__m;
  std::stack<Cell> __history;

public:
  MazeSolver(Maze &);
  ~MazeSolver();
  void solve();
  void printSolution();
  Maze *solution();
};

#endif
