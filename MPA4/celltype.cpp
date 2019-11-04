#include "celltype.hpp"

CellType getCellTypeRepresentation(char x) {
  switch (x) {
  case '#':
    return CellType::Wall;
  case '.':
    return CellType::Open;
  case 'o':
    return CellType::Source;
  case '*':
    return CellType::Destination;
  case 'x':
    return CellType::Visited;
  case '&':
    return CellType::Deadend;
  default:
    return CellType::Wall;
  }
}

char getCharRepresentation(CellType c) {
  switch (c) {
  case CellType::Wall:
    return '#';
  case CellType::Open:
    return '.';
  case CellType::Source:
    return 'o';
  case CellType::Destination:
    return '*';
  case CellType::Visited:
    return 'x';
  case CellType::Deadend:
    return '.';
  default:
    return '#';
  }
}
