#ifndef MPA4_MAZESOLVER
#define MPA4_MAZESOLVER

#include "agenda.hpp"
#include "maze.hpp"
#include <string>

template <class T> class MazeSolver {
private:
  Agenda<T> __a;
  Maze *__m;

public:
  MazeSolver(Maze &);
  ~MazeSolver();
  void solve();
  Maze *solution();
};

#endif
