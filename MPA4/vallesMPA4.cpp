#include <fstream>
#include <iostream>

#include "coordinates.hpp"
#include "maze.hpp"

std::string readFile();
int main() {
  std::string input = "########...#o##*#...########";
  Maze a(input, Coordinates(7, 4));
  std::cout << a.stringRepresentation() << std::endl;
  return 0;
}
