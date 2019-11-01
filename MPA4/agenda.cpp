#include "agenda.hpp"

template <class T> Agenda<T>::Agenda() {
  __adt = new T();
  std::string t1 = typeid(*__adt).name();
  std::string t2 = typeid(std::stack<Cell>).name();
  std::string t3 = typeid(std::queue<Cell>).name();
}

template <class T> Agenda<T>::~Agenda() { delete __adt; }

template <class T> void Agenda<T>::add(Cell c) { __adt->push(c); }

template <class T> bool Agenda<T>::remove() {
  if (__adt->empty()) {
    return false;
  } else {
    __adt->pop();
    return true;
  }
}

template <class T> bool Agenda<T>::isEmpty() { return __adt->empty(); }

template <class T> int Agenda<T>::size() { return __adt->size(); }

template <> Cell Agenda<std::stack<Cell>>::latest() { return __adt->top(); }

template <> Cell Agenda<std::queue<Cell>>::latest() { return __adt->front(); }

template class Agenda<std::stack<Cell>>;
template class Agenda<std::queue<Cell>>;
