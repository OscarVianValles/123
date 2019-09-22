#ifndef MPA2_CONDITION
#define MPA2_CONDITION

#include <string>

class Condition {
private:
  enum Conditions { less = 1 << 0, greater = 1 << 1, equal = 1 << 2 };

  bool _isNumber;            // Stores if the condition is a number
  int _conditionType;        // Condition type i.e. <, >, <=
  int _conditionNumber;      // Condition if it is a number
  std::string _conditionVar; // Condition if it is a variable

  bool _isRoot;    // a bool to check if the operator is logarithmic
  int _rootNumber; // Stores the root number, ie 2 if sqr root;
public:
  int getCount();
  bool getIsNumber();
  bool getIsRoot();
  int getRootNumber();
  void tokenize(std::string rawCondition, int iteratorLength);
};

#endif
