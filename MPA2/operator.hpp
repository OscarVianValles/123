#ifndef MPA2_OPERATOR
#define MPA2_OPERATOR

#include <string>

class Operator {
private:
  enum Operators { plus, minus, multiply, divide, modulo, logarithm };

  bool _isLog; // a bool to check if the operator is logarithmic
  int _logBase;
  int _operatorType;   // Operator type i.e. +, -, =
  int _operatorNumber; // The value that is being used to modify the iterator

public:
  int getCount();
  bool getIsLog();
  bool getLogBase();
  void tokenize(std::string rawOperator);
};

#endif
