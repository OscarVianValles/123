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
  bool append(Term &input);
  bool multiply(Term &input);

  bool applySummation(bool isUpperLimitNumber, bool isLogarithmic,
                      int lowerLimit, int upperLimitInt,
                      std::string upperLimitString, int logarithmicBase);
  void printTerms() const;
};

#endif
