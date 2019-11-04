#include "cell.hpp"

Cell::Cell() {
  __type = CellType::Wall;
  __location.x = 0;
  __location.y = 0;
  __visited = false;
}

Cell::Cell(CellType t, int x, int y, bool visited) : __location(x, y) {
  __type = t;
  __visited = visited;
}

Cell::Cell(CellType t, Coordinates l, bool visited) {
  __type = t;
  __location = l;
  __visited = visited;
}

void Cell::visit() { __type = CellType::Visited; }

void Cell::close() {
  __type = __type != CellType::Source ? CellType::Deadend : CellType::Source;
}

CellType Cell::type() { return __type; }

Coordinates Cell::location() { return __location; }

bool Cell::isVisited() { return __visited; }
