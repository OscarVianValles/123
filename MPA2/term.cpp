#include "term.hpp"

Term::Term() {
  _infinite = false;
  _coefficient = 1;
  _coefficientDenominator = 1;
  _exponent = 1;
  _variable = 'x';
}

Term::Term(int coefficient, int exponent) {
  _infinite = false;
  this->_coefficient = coefficient;
  this->_exponent = exponent;
  _variable = 'x';
  _coefficientDenominator = 1;
}

Term::Term(int coefficient, int exponent, char variable) {
  _infinite = false;
  this->_coefficient = coefficient;
  this->_exponent = exponent;
  this->_variable = variable;
  _coefficientDenominator = 1;
}

Term::Term(bool isInfinite) { _infinite = isInfinite; }

int Term::getCoefficient() const { return _coefficient; }

int Term::getCoefficientDenominator() const { return _coefficientDenominator; }

int Term::getExponent() const { return _exponent; }

std::string Term::getVariable() const { return _variable; }

bool Term::addCoefficient(int x) {
  _coefficient += x;
  return true;
}

bool Term::multiplyTerm(Term &input) {
  _exponent += input.getExponent();
  _coefficient *= input.getCoefficient();
  return true;
}

bool Term::divide(int divisor) {
  if (_exponent != 0) {
    if (_coefficient % divisor != 0) {
      _coefficientDenominator = divisor;

      if ((_coefficientDenominator < 0 && _coefficient < 0) ||
          (_coefficientDenominator < 0 && _coefficient >= 0)) {
        _coefficientDenominator *= -1;
        _coefficient *= -1;
      }
    } else {
      _coefficient /= divisor;
    }
  }

  return true;
}

bool Term::applySummation(bool isUpperLimitNumber, bool isLogarithmic,
                          int lowerLimit, int upperLimitInt,
                          std::string upperLimitString, int logarithmicBase) {

  if (isLogarithmic) {
    _variable = upperLimitString;
    _exponent = -logarithmicBase;

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
