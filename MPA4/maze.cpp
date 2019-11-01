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

// Tokenizes input string to a maze.
// TODO: Refactor to accept strings with newlines
void Maze::__tokenize(std::string input) {
  for (int i = 0; i < __dimensions.y; i++) {

    // Loops through the first $__dimensions.x characters in the string and
    // creates a cell based on the character
    for (int j = 0; j < __dimensions.x; j++) {
      __maze[i][j] = Cell(getCellTypeRepresentation(input[j]),
                          static_cast<int>(j), static_cast<int>(i), false);
    }

    // Erases the first $__dimensions.x characters in the string so that the
    // next loop can create cells based on the correct characters
    input.erase(0, __dimensions.x);
  }
}

// Visits the cell at coordinate c
void Maze::visit(Coordinates c) { __maze[c.y][c.x].visit(); }

// Builders
Coordinates Maze::dimensions() const { return __dimensions; }

// Creates a string representation based on the cells. Can be configured to not
// include newlines, which is used in the copy constructor
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

// Finds the source of the maze
Coordinates Maze::source() const {
  for (int i = 0; i < __dimensions.y; i++) {
    for (int j = 0; j < __dimensions.x; j++) {
      if (__maze[i][j].type() == CellType::Source) {
        return Coordinates(j, i);
      }
    }
  }
  return Coordinates(-1, -1);
}

// Gets the cell at coordinate c. if coordinate c is out of bounds, returns a
// wall which cannot be accessed
Cell Maze::at(Coordinates c) const {
  return c < __dimensions ? __maze[c.y][c.x] : Cell();
}
