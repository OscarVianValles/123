#include "maze.hpp"

Maze::Maze(std::string input, int row, int col) : __dimensions(col, row) {
  __allocateMem();
  __tokenize(input);
}

Maze::Maze(std::string input, Coordinates d) {
  __dimensions = d;
  __allocateMem();
  __tokenize(input);
}

Maze::Maze(const Maze &input) {
  __dimensions = input.dimensions();
  __allocateMem();
  __tokenize(input.stringRepresentation(false));
}

Maze::~Maze() {
  for (int i = 0; i < __dimensions.y; i++) {
    delete[] __maze[i];
  }

  delete[] __maze;
}

// Allocates memory for the maze
void Maze::__allocateMem() {
  // Allocate for each row
  __maze = new Cell *[__dimensions.y];

  // Allocate for each column
  for (int i = 0; i < __dimensions.y; i++)
    __maze[i] = new Cell[__dimensions.x];
}

// Tokenizes input string to a maze
void Maze::__tokenize(std::string input) {
  for (int i = 0; i < __dimensions.y; i++) {
    for (int j = 0; j < __dimensions.x; j++) {
      __maze[i][j] = Cell(getCellTypeRepresentation(input[j]),
                          static_cast<int>(j), static_cast<int>(i), false);
    }
    input.erase(0, __dimensions.x);
  }
}

// Builders
Coordinates Maze::dimensions() const { return __dimensions; }

std::string Maze::stringRepresentation(bool withNewline) const {
  std::string maze;
  for (int i = 0; i < __dimensions.y; i++) {
    for (int j = 0; j < __dimensions.x; j++) {
      maze += (getCharRepresentation(__maze[i][j].type()));
    }

    if (withNewline) {
      maze += '\n';
    }
  }
  return maze;
}
