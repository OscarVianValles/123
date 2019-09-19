#include "term.hpp"

int Term::getCoefficient() const { return _coefficient; }

int Term::getExponent() const { return _exponent; }

char Term::getVariable() const { return _variable; }

bool Term::addCoefficient(int x) {
  _coefficient += x;
  return true;
}

bool Term::multiplyTerm(Term &input) {
  _exponent += input.getExponent();
  _coefficient *= input.getCoefficient();
  return true;
}

bool Term::applySummation(bool isNumber, int lowerLimit, int upperLimitInt,
                          std::string upperLimitString) {
  if (isNumber) {
    // Checking if lowerLimit is is less than the upperlimit
    if (lowerLimit > upperLimitInt) {
      _coefficient = 0;
      _exponent = 0;
      return true;
    }

    // Checking if the lowerLimit is not equal to 1, then normalizes it
    if (lowerLimit != 1) {
      upperLimitInt = upperLimitInt - lowerLimit + 1;
      lowerLimit = 1;
    }

    // Checking if the content of the term is constant
    if (_exponent == 0) {
      _coefficient *= upperLimitInt;
      return true;
    }
  }

  return false;
}

Term::Term() {
  _coefficient = 1;
  _exponent = 1;
  _variable = 'x';
}

Term::Term(int coefficient, int exponent) {
  this->_coefficient = coefficient;
  this->_exponent = exponent;
  _variable = 'x';
}

Term::Term(int coefficient, int exponent, char variable) {
  this->_coefficient = coefficient;
  this->_exponent = exponent;
  this->_variable = variable;
}
