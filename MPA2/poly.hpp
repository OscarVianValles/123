#ifndef MPA2_POLY
#define MPA2_POLY

#include "term.hpp"
#include <cmath>
#include <iostream>
#include <limits>
#include <list>

class Poly {
private:
  std::list<Term> terms;

public:
  bool operator+=(Term &input);
  bool operator*=(Term &input);

  bool applySummation(bool isNumber, int lowerLimit, int upperLimitInt,
                      std::string upperLimitString);
  void printTerms() const;
};

#endif
