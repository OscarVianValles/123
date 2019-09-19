#include "poly.hpp"

bool Poly::operator+=(Term &input) {

  // Handle if terms are empty
  if (terms.empty()) {
    terms.push_back(input);
    return true;
  }

  // Saving input data to reduce function calls
  const char inputVariable = input.getVariable();
  const int inputCoefficient = input.getCoefficient();
  const int inputExponent = input.getExponent();

  int prevExponent = std::numeric_limits<int>::max();
  auto i = terms.begin();
  // Looping through each member of terms
  for (; i != terms.end(); ++i) {

    // Saving i data to reduce function calls
    auto &curr = *i;
    const char currVariable = curr.getVariable();
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

bool Poly::operator*=(Term &input) {
  for (auto &i : terms) {
    if (i.multiplyTerm(input) == false) {
      return false;
    }
  }

  return true;
}

// Apply summation to all members of the polynomial
bool Poly::applySummation(bool isNumber, int lowerLimit, int upperLimitInt,
                          std::string upperLimitString) {
  for (auto &i : terms) {
    if (i.applySummation(isNumber, lowerLimit, upperLimitInt,
                         upperLimitString) == false) {
      return false;
    }
  }

  return true;
}

// Prints the terms
void Poly::printTerms() const {
  for (auto i = terms.begin(); i != terms.end(); ++i) {
    auto &curr = *i;
    const int currCoefficient = curr.getCoefficient();
    if (i != terms.begin()) {
      std::cout << ((currCoefficient < 0) ? " - " : " + ");
    } else {
      std::cout << ((currCoefficient < 0) ? "-" : "");
    }
    std::cout << std::abs(currCoefficient) << curr.getVariable() << "^"
              << curr.getExponent();
  }

  std::cout << std::endl;
}
