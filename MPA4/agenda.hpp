#ifndef MPA4_AGENDA
#define MPA4_AGENDA

#include "cell.hpp"
#include <queue>
#include <stack>
#include <string>

template <class T> class Agenda {
private:
  T *__adt;

public:
  Agenda();
  ~Agenda();
  void add(Cell);
  bool remove();
  bool isEmpty();
  int size();
  Cell latest();
};
#endif
