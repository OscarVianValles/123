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
      _tokenizeIterator(token.substr(3, token.length() - 3));
      break;
    case 1:
      _tokenizeCondition(token);
      break;
    case 2:
      _operator = token;
      break;
    default:
      break;
    }

    counter++;
  }
}

void Loop::_tokenizeIterator(std::string rawIterator) {

  // Creating buffer variables
  std::istringstream tempStream(rawIterator);
  std::string token;
  int counter = 0;

  while (std::getline(tempStream, token, '=')) {
    switch (counter) {
    case 0:
      _iterator = token;
      break;
    case 1:
      _counter = token;
      if (isNumber(token)) {
        _counterNumber = stoi(token);
      } else {
        _counterVar = token;
      }
      break;
    default:
      break;
    }

    counter++;
  }
}

void Loop::_tokenizeCondition(std::string rawCondition) {
  rawCondition = rawCondition.substr(
      _iterator.length(), rawCondition.length() - _iterator.length());

  unsigned int conditionLength = 1, i = 0, sqrtCount = 0;
  switch (rawCondition[0]) {

  case '<': {
    if (rawCondition[1] == '=') {
      _conditionType = Conditions::less | Conditions::equal;
      conditionLength++;
    } else {
      _conditionType = Conditions::less;
    }
    break;
  }

  case '>': {
    if (rawCondition[1] == '=') {
      _conditionType = Conditions::greater | Conditions::equal;
      conditionLength++;
    } else {
      _conditionType = Conditions::greater;
    }
    break;
  }

  case '=': {
    if (rawCondition[1] == '=') {
      _conditionType = Conditions::equal;
      conditionLength++;
    }
    break;
  }

  case '*': {
    while (rawCondition[i] != '<' || rawCondition[i] != '>' ||
           rawCondition[i] != '=') {
      if (rawCondition[i] == _iterator[i]) {
        // Delete Iterator from condition
        rawCondition = rawCondition.substr(
            _iterator.length(), rawCondition.length() - _iterator.length());
        // Correct I
        i -= _iterator.length();
      } else {
        // Counts the number of multipliers in the condition
        conditionLength++;
        sqrtCount++;
        i++;
      }
    }

  default:
    break;
  }
  }

  // Handling numbers
  rawCondition = rawCondition.substr(conditionLength,
                                     rawCondition.length() - conditionLength);

  if (sqrtCount > 0) {
    _conditionSqrtCount = ++sqrtCount;
  }
  if (isNumber(rawCondition)) {
    _conditionNumber = stoi(rawCondition);
  } else {
    _conditionVar = rawCondition;
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
  Term procedures(_countProcedures(), 0);
  procedures.applySummation(true, _counterNumber, _conditionNumber, "");
  polyCount += procedures;
}

int Loop::_countProcedures() {
  int count;
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
