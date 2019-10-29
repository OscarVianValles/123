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
  default:
    return '#';
  }
}
