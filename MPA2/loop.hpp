#ifndef MPA2_LOOP
#define MPA2_LOOP

#include <iostream>
#include <list>
#include <sstream>
#include <string>

#include "poly.hpp"
#include "utils.hpp"

// creating loop class
class Loop {

public:
  std::string getIterator();
  std::string getCondition();
  std::string getOperator();
  std::string getProcedures();

  void tokenize(std::string file);
  void count();
  void printMembers();
  void printCount();

private:
  std::string _iterator;

  std::string _counter;
  int _counterNumber;
  std::string _counterVar;

  std::string _condition;
  int _conditionType;
  int _conditionNumber;
  int _conditionSqrtCount;
  std::string _conditionVar;

  std::string _operator;
  int _operatorType;
  int _operatorNumber;

  std::list<std::string> _procedures;

  Poly polyCount;

  void _tokenizeParenContent(std::string &parenContent);
  void _tokenizeIterator(std::string rawIterator);
  void _tokenizeCondition(std::string rawCondition);
  void _tokenizeOperator(std::string rawOperator);
  void _tokenizeBracketContent(std::string &bracketContent);

  int _countProcedures();
  int _countUpperLimit();
};

#endif
