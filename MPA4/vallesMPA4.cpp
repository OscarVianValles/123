#include <fstream>
#include <iostream>

#include "agenda.hpp"
#include "coordinates.hpp"
#include "maze.hpp"
#include "mazesolver.hpp"
#include <stack>

std::string readFile();
int main() {
  std::string input = "########...#o##*....########";
  Maze a(input, Coordinates(7, 4));
  MazeSolver<std::stack<Cell>> b(a);
  b.solve();
  b.printSolution();

  MazeSolver<std::queue<Cell>> c(a);
  c.solve();
  c.printSolution();

  return 0;
}
