#ifndef MPA4_MAZESOLVER
#define MPA4_MAZESOLVER

#include "agenda.hpp"
#include "coordinates.hpp"
#include "maze.hpp"
#include <stack>
#include <string>

template <class T> class MazeSolver {
private:
  Agenda<T> __a;
  Maze *__m;
  std::stack<Coordinates> __history;

public:
  MazeSolver(Maze &);
  ~MazeSolver();

  void solve();

  std::string solution();
};

#endif
