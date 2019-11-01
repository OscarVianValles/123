#include "mazesolver.hpp"
#include <iostream>

template <class T> MazeSolver<T>::MazeSolver(Maze &m) {
  __m = new Maze(m);
  __currentLocation = __m->source();
}

template <class T> MazeSolver<T>::~MazeSolver() { delete __m; }

template <class T> void MazeSolver<T>::solve() {
  bool isSolved = false, openIsFound = false;
  while (!isSolved) {
    // Creating agenda for the checks
    openIsFound = false;
    __a.add(__m->at(Coordinates(__currentLocation.x - 1, __currentLocation.y)));
    __a.add(__m->at(Coordinates(__currentLocation.x, __currentLocation.y - 1)));
    __a.add(__m->at(Coordinates(__currentLocation.x + 1, __currentLocation.y)));
    __a.add(__m->at(Coordinates(__currentLocation.x, __currentLocation.y + 1)));

    while (!__a.isEmpty()) {
      if (__a.latest().type() == CellType::Open && !openIsFound) {
        __currentLocation = __a.latest().location();
        __m->visit(__currentLocation);
        openIsFound = true;
      } else if (__a.latest().type() == CellType::Destination) {
        isSolved = true;
        break;
      }
      __a.remove();
    }
  }
}

template <class T> void MazeSolver<T>::printSolution() {
  std::cout << __m->stringRepresentation(true) << std::endl;
}

// To compile, the compiler must now which templates are needed so that the
// linker can connect the different files
template class MazeSolver<std::stack<Cell>>;
template class MazeSolver<std::queue<Cell>>;
