#include "poly.hpp"

bool Poly::append(Term &input) {

  // Handle if terms are empty
  if (terms.empty()) {
    terms.push_back(input);
    return true;
  }

  // Saving input data to reduce function calls
  const std::string inputVariable = input.getVariable();
  const int inputCoefficient = input.getCoefficient();
  const int inputExponent = input.getExponent();

  int prevExponent = std::numeric_limits<int>::max();
  auto i = terms.begin();
  // Looping through each member of terms
  for (; i != terms.end(); ++i) {

    // Saving i data to reduce function calls
    auto &curr = *i;
    const std::string currVariable = curr.getVariable();
    const int currExponent = curr.getExponent();

    // Check if variables are the same
    if (inputVariable == currVariable) {

      // Adding to the coefficient if exponents are the same
      if (inputExponent == currExponent) {
        curr.addCoefficient(inputCoefficient);
        return true;
      }

      // Checks if prevExponent > inputExponent > currExponent which means that
      // it should be added in between
      else if (prevExponent > inputExponent && currExponent < inputExponent) {
        terms.insert(i, input);
        return true;
      }

    } else if (inputVariable < currVariable) {
      terms.insert(++i, input);
      return true;
    }

    prevExponent = currExponent;
  }

  if (i == terms.end()) {
    terms.push_back(input);
    return true;
  }

  return false;
}

bool Poly::multiply(Term &input) {
  for (auto &i : terms) {
    if (i.multiplyTerm(input) == false) {
      return false;
    }
  }

  return true;
}

// Apply summation to all members of the polynomial
bool Poly::applySummation(bool isUpperLimitNumber, bool isLogarithmic,
                          int lowerLimit, int upperLimitInt,
                          std::string upperLimitString, int logarithmicBase) {
  for (auto it = terms.begin(); it != terms.end(); it++) {

    // If upper limit is not a number and the lower limit is != 1, a formula is
    // applied to get the summation
    if ((!isUpperLimitNumber || isLogarithmic) && lowerLimit != 1) {

      // Create new term for the constant part of the formula
      Term newTerm(0 - it->getCoefficient(), it->getExponent());

      // apply summation to both
      it->applySummation(isUpperLimitNumber, isLogarithmic, 1, upperLimitInt,
                         upperLimitString, logarithmicBase);
      newTerm.applySummation(true, false, 1, lowerLimit - 1, "",
                             logarithmicBase);

      // Append new term
      this->append(newTerm);

      // skips the next term
      it++;
    } else {

      // If upper limit is a number, normal summation rules are applied
      if (it->applySummation(isUpperLimitNumber, isLogarithmic, lowerLimit,
                             upperLimitInt, upperLimitString,
                             logarithmicBase) == false) {
        return false;
      }
    }
  }

  return true;
}

// Prints the terms
void Poly::printTerms() const {
  for (auto i = terms.begin(); i != terms.end(); ++i) {
    auto &curr = *i;
    const int currCoefficient = curr.getCoefficient();
    const int currExponent = curr.getExponent();
    const int currFunctionNumber = curr.getFunctionNumber();
    const std::string currVariable = curr.getVariable();
    const Term::Function currType = curr.getType();

    std::string currVariableString = "";

    // Handle all variable printing depending on exponent
    if (currExponent > 1) {
      currVariableString.append(currVariable);
      currVariableString.append("^");
      currVariableString.append(std::to_string(currExponent));
    } else if (currExponent == 1) {
      currVariableString = currVariable;
    }

    // Handle prepending + or - depending on sign
    if (i != terms.begin()) {
      std::cout << ((currCoefficient < 0) ? " - " : " + ");
    } else {
      std::cout << ((currCoefficient < 0) ? "-" : "");
    }

    if (currType == Term::Function::log) {
      std::cout << std::abs(currCoefficient) << " log(" << currFunctionNumber
                << ") " << currVariableString;
    } else {
      std::cout << std::abs(currCoefficient) << currVariableString;
    }
  }

  std::cout << std::endl;
}
