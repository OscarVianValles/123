#ifndef MPA4_CELL
#define MPA4_CELL

#include "celltype.hpp"
#include "coordinates.hpp"

class Cell {
private:
  CellType __type;
  Coordinates __location;
  bool __visited;

public:
  Cell();
  Cell(CellType, int, int, bool);
  Cell(CellType, Coordinates, bool);

  void visit();
  void close();

  CellType type();
  Coordinates location();
  bool isVisited();
};

#endif
