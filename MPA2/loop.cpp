#include "loop.hpp"

void Loop::tokenize(std::string file) {
  // Gets the next character after the parenthesis
  unsigned openParen = file.find("(") + 1;

  // Gets the length of the contents of the parenthesis by getting the position
  // of the close parenthesis and subtracting the number of characters from the
  // start of the loop declaration to the character after the first parenthesis
  unsigned parenLen = file.find(")") - openParen;

  // Gets the next character after the close bracket;
  unsigned openBracket = file.find("{") + 1;

  // Same logic is follewed from parenLen
  unsigned bracketLen = file.find_last_of("}") - openBracket;

  // Gets the content of the parenthesis

  std::string parenContent = file.substr(openParen, parenLen);
  std::string bracketContent = file.substr(openBracket, bracketLen);

  _tokenizeParenContent(parenContent);
  _tokenizeBracketContent(bracketContent);
}

void Loop::_tokenizeParenContent(std::string &parenContent) {

  // Creating buffer variables
  std::istringstream tempStream(parenContent);
  std::string token;
  int counter = 0;

  // Tokenizing the string
  while (std::getline(tempStream, token, ';')) {
    switch (counter) {
    case 0:
      // Tokenizes the iterator which returns the counter, which is then
      // tokenized;
      _counter.tokenize(_iterator.tokenize(token));
      break;
    case 1:
      _condition.tokenize(token, _iterator.getIterator().length());
      break;
    case 2:
      _operator.tokenize(token);
      break;
    default:
      break;
    }

    counter++;
  }
}

void Loop::_tokenizeBracketContent(std::string &bracketContent) {
  // Creating buffer variables
  std::istringstream tempStream(bracketContent);
  std::string token;

  while (std::getline(tempStream, token, ';')) {

    // Finding if operator modifier is inside the main loop
    // TODO: Make it more robust
    int operatorLocation = token.find(_iterator);
    if (operatorLocation != std::string::npos && _operator.empty()) {
      operatorLocation += _iterator.length();

      // Logical XOR Operator. This is done to get += =iter+1 and other
      // operators that can operate on the iterator but not ==
      if ((!(token[operatorLocation] == '=') !=
           !(token[operatorLocation + 1] == '=')) ||
          ((token[operatorLocation] == '+' &&
            token[operatorLocation + 1] == '+')) ||
          ((token[operatorLocation] == '-' &&
            token[operatorLocation - 1] == '-'))) {
        _operator = token;
      }
    } else {
      _procedures.push_back(token);
    }
  }
}

void Loop::printMembers() {
  std::cout << "==========[ Loop ]==========" << std::endl
            << "Iterator: " << _iterator << std::endl
            << "Intial Counter Number: " << _counterNumber << std::endl
            << "Intial Counter Var: " << _counterVar << std::endl
            << "Condition Type: " << getConditionRepresentation(_conditionType)
            << std::endl
            << "Condition Number: " << _conditionNumber << std::endl
            << "Condition Var: " << _conditionVar << std::endl
            << "Operator: " << (_operator.empty() ? "Empty" : _operator)
            << std::endl
            << std::endl
            << "Procedures: " << std::endl;

  for (auto &i : _procedures) {
    std::cout << i << std::endl;
  }

  std::cout << std::endl;
}

void Loop::count() {
  Term inLoop(_countProcedures() + _countParametersInLoop(), 0);
  inLoop.applySummation(true, _counterNumber, _conditionNumber, "");
  polyCount += inLoop;
  Term afterLoop(_countParametersAfterLoop(), 0);
  polyCount += afterLoop;
}

int Loop::_countParametersInLoop() {
  int count = 0;

  // Get count from condition
  if (_conditionType <= Conditions::equal) {
    count++;
  }

  // Get count from operators
  if (_operatorType <= Operators::modulo) {
    count++;
  }

  return count;
}

int Loop::_countParametersAfterLoop() {
  int count = 0;

  // Get count from iterator
  count++;

  // Get count from condition
  if (_conditionType <= Conditions::equal) {
    count++;
  }

  return count;
}

int Loop::_countProcedures() {
  int count = 0;
  for (auto &i : _procedures) {
    for (auto &j : i) {
      if (j == '+' || j == '-' || j == '*' || j == '/' || j == '=') {
        count++;
      }
    }
  }
  return count;
}

void Loop::printCount() { polyCount.printTerms(); }
