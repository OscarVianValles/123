#include "utils.hpp"

// Checking if entire string is a number. From
// https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c

// Creating Conditions Enums and Representation Function;
std::string getConditionRepresentation(int conditionType) {
  std::string condition;

  if (conditionType & Conditions::less) {
    condition.append(1, '<');
  }

  if (conditionType & Conditions::greater) {
    condition.append(1, '>');
  }

  if (conditionType & Conditions::equal) {
    condition.append(1, '=');
  }

  return condition;
}

// Creating Operators Enums and Representation Function;

std::string getOperatorRepresentation(int operatorType) {
  std::string representation;

  switch (operatorType) {
  case Operators::plus:
    return representation.append(1, '+');
  case Operators::minus:
    return representation.append(1, '-');
  case Operators::multiply:
    return representation.append(1, '*');
  case Operators::divide:
    return representation.append(1, '/');
  case Operators::modulo:
    return representation.append(1, '%');
  default:
    return representation;
  }
}

bool isNumber(std::string &s) {
  return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}
