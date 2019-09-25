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
  bool divide(int divisor);

  bool applySummation(bool isUpperLimitNumber, bool isLogarithmic, bool isRoot,
                      int lowerLimit, int upperLimitInt,
                      std::string upperLimitString);
  void printTerms() const;
  std::list<Term> getTerms() const;
};

#endif
