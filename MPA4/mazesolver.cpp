#include "mazesolver.hpp"
#include <iostream>

template <class T> MazeSolver<T>::MazeSolver(Maze &m) { __m = new Maze(m); }

template <class T> MazeSolver<T>::~MazeSolver() { delete __m; }

// Solves the maze
template <class T> void MazeSolver<T>::solve() {

  Coordinates previousLocation,
      currentLocation = previousLocation = __m->source();

  bool isSolved = false, openIsFound = false;
  while (!isSolved) {
    openIsFound = false;

    // Creating next cells to be checked

    // Left
    __a.add(__m->at(Coordinates(currentLocation.x - 1, currentLocation.y)));

    // Up
    __a.add(__m->at(Coordinates(currentLocation.x, currentLocation.y - 1)));

    // Right
    __a.add(__m->at(Coordinates(currentLocation.x + 1, currentLocation.y)));

    // Down
    __a.add(__m->at(Coordinates(currentLocation.x, currentLocation.y + 1)));

    previousLocation = currentLocation;
    // Finding first open space and clearing agenda
    while (!__a.isEmpty()) {

      // Find first open space
      if (__a.latest().type() == CellType::Open && !openIsFound) {

        // Set current location based on cell that is open
        currentLocation = __a.latest().location();

        // Visit the open cell
        __m->visit(currentLocation);

        // Add the current cell to the stack
        __history.push(currentLocation);

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

    // If previous location is the same as current location then that means the
    // the current location is a deadend.
    if (previousLocation == currentLocation && !isSolved) {

      // Set current location as a deadend
      __m->close(currentLocation);

      // Clear current location from history
      // if the size of the history is greater than 1, then there are still
      // previous cells to go back to. If it less than 1, then that means we
      // have gone back to the source cell, meaning that there is no solution to
      // the maze
      if (__history.size() > 1) {
        __history.pop();
      } else {
        return;
      }

      // Set current location to be the cell before the deadend
      currentLocation = __history.top();
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
