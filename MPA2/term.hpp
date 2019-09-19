#ifndef MPA2_TERM
#define MPA2_TERM

#include <iostream>
#include <string>

class Term {
private:
  int _coefficient;
  int _exponent;
  char _variable;

public:
  int getCoefficient() const;
  int getExponent() const;
  char getVariable() const;

  bool addCoefficient(int x);
  bool multiplyTerm(Term &input);

  bool applySummation(bool isNumber, int lowerLimit, int upperLimitInt,
                      std::string upperLimitString);

  Term();
  Term(int coefficient, int exponent);
  Term(int coefficient, int exponent, char variable);
};

#endif
