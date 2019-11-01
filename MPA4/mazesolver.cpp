#include "mazesolver.hpp"

template <class T> MazeSolver<T>::MazeSolver(Maze &m) { __m = new Maze(m); }
template <class T> MazeSolver<T>::~MazeSolver() { delete __m; }

template class MazeSolver<std::stack<Cell>>;
template class MazeSolver<std::queue<Cell>>;
