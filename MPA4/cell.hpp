#ifndef MPA4_CELL
#define MPA4_CELL

enum class CellType { Wall, Open, Source, Destination };

struct Coordinates {
  int x, y;
};

class Cell {
private:
  CellType __type;
  Coordinates __location;
  bool __visited;

public:
  Cell();
  Cell(CellType, int, int, bool);
  Cell(CellType, Coordinates, bool);

  CellType type();
  Coordinates location();
  bool isVisited();
};

#endif
