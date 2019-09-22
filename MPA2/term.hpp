#ifndef MPA2_TERM
#define MPA2_TERM

#include <iostream>
#include <string>

class Term {

public:
  Term();
  Term(int coefficient, int exponent);
  Term(int coefficient, int exponent, char variable);

  enum Function { none, root, log };

  int getCoefficient() const;
  int getExponent() const;
  std::string getVariable() const;
  Term::Function getType() const;
  int getFunctionNumber() const;

  bool addCoefficient(int x);
  bool multiplyTerm(Term &input);

  bool applySummation(bool isUpperLimitVariable, bool isLogarithmic,
                      int lowerLimit, int upperLimitInt,
                      std::string upperLimitString, int logarithmicBase);

private:
  int _coefficient;
  int _exponent;
  std::string _variable;
  Term::Function _type;
  int _functionNumber;
};

#endif
