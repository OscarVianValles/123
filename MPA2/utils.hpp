#ifndef MPA2_UTILS
#define MPA2_UTILS

#include <algorithm>
#include <string>

std::string getConditionRepresentation(int conditionType);
std::string getOperatorRepresentation(int operatorType);
bool isNumber(std::string &s);

enum Conditions { less = 1 << 0, greater = 1 << 1, equal = 1 << 2 };
enum Operators { plus, minus, multiply, divide, modulo, logarithm };

#endif
