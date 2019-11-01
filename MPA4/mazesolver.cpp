#include "mazesolver.hpp"
#include <iostream>

template <class T> MazeSolver<T>::MazeSolver(Maze &m) {
  __m = new Maze(m);
  __currentLocation = __m->source();
}

template <class T> MazeSolver<T>::~MazeSolver() { delete __m; }

// Solves the maze
template <class T> void MazeSolver<T>::solve() {
  bool isSolved = false, openIsFound = false;
  while (!isSolved) {
    // Resetting flags
    openIsFound = false;

    // Creating next cells to be checked

    // Left
    __a.add(__m->at(Coordinates(__currentLocation.x - 1, __currentLocation.y)));

    // Up
    __a.add(__m->at(Coordinates(__currentLocation.x, __currentLocation.y - 1)));

    // Right
    __a.add(__m->at(Coordinates(__currentLocation.x + 1, __currentLocation.y)));

    // Down
    __a.add(__m->at(Coordinates(__currentLocation.x, __currentLocation.y + 1)));

    // Finding first open space and clearing agenda
    while (!__a.isEmpty()) {

      // Find first open space
      if (__a.latest().type() == CellType::Open && !openIsFound) {

        // Set current location based on cell that is open
        __currentLocation = __a.latest().location();

        // Visit the open cell
        __m->visit(__currentLocation);

        // Set flag
        openIsFound = true;
      }

      // if the adjacent to the cell is the destination, end the loop. if in the
      // previous adjacent cells to be checked, an open cell is found, skips
      // this check
      else if (__a.latest().type() == CellType::Destination && !openIsFound) {
        isSolved = true;
        break;
      }

      // Removes the current cell being checked
      __a.remove();
    }
  }
}

template <class T> std::string MazeSolver<T>::solution() {
  return __m->stringRepresentation(true);
}

// To compile, the compiler must know which templates are needed so that the
// linker can connect the different files
template class MazeSolver<std::stack<Cell>>;
template class MazeSolver<std::queue<Cell>>;
