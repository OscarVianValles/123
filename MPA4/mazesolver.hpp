#ifndef MPA4_MAZESOLVER
#define MPA4_MAZESOLVER

#include "agenda.hpp"
#include "maze.hpp"

template <class T> class MazeSolver {
private:
  Agenda<T> *a;
  Maze *m;

public:
  MazeSolver(Maze);
  ~MazeSolver();
  void solve();
  void writeSolution();
};

#endif
