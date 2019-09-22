#include "term.hpp"

Term::Term() {
  _coefficient = 1;
  _exponent = 1;
  _variable = 'x';
  _type = Function::none;
  _functionNumber = 0;
}

Term::Term(int coefficient, int exponent) {
  this->_coefficient = coefficient;
  this->_exponent = exponent;
  _variable = 'x';
  _type = Function::none;
  _functionNumber = 0;
}

Term::Term(int coefficient, int exponent, char variable) {
  this->_coefficient = coefficient;
  this->_exponent = exponent;
  this->_variable = variable;
  _type = Function::none;
  _functionNumber = 0;
}
int Term::getCoefficient() const { return _coefficient; }

int Term::getExponent() const { return _exponent; }

std::string Term::getVariable() const { return _variable; }

Term::Function Term::getType() const { return _type; }

int Term::getFunctionNumber() const { return _functionNumber; }

bool Term::addCoefficient(int x) {
  _coefficient += x;
  return true;
}

bool Term::multiplyTerm(Term &input) {
  _exponent += input.getExponent();
  _coefficient *= input.getCoefficient();
  return true;
}

bool Term::applySummation(bool isUpperLimitNumber, bool isLogarithmic,
                          int lowerLimit, int upperLimitInt,
                          std::string upperLimitString, int logarithmicBase) {

  if (isLogarithmic) {
    _type = Function::log;
    _functionNumber = logarithmicBase;
    _variable = upperLimitString;
    _exponent = 1;

  } else if (isUpperLimitNumber) {
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
  } else {
    _variable = upperLimitString;
    _exponent = 1;
  }

  return false;
}
