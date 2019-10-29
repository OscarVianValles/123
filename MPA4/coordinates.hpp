#ifndef MPA4_COORDINATES
#define MPA4_COORDINATES

struct Coordinates {
  int x, y;

  Coordinates() {
    x = 0;
    y = 0;
  }

  Coordinates(int a, int b) {
    x = a;
    y = b;
  }
};

#endif
