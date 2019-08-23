#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>

void readFile(std::ifstream &input, std::list<std::string> &loopHolder);
void tokenizeLoops(std::list<std::string> &loopHolder);
bool isNumber(std::string &in);
// Creating Conditions Enums and Representation Function;
enum Conditions { less = 1 << 0, greater = 1 << 1, equal = 1 << 2 };
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
enum Operators { plus, minus, multiply, divide, modulo };
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

// Creating Loop Class
class Loop {

public:
  std::string getIterator();
  std::string getCondition();
  std::string getOperator();
  std::string getProcedures();

  void tokenize(std::string file);
  void printMembers();

private:
  std::string _iterator;
  std::string _counter;
  int _counterNumber;
  std::string _counterVar;
  std::string _condition;
  int _conditionType;
  int _conditionNumber;
  std::string _conditionVar;
  std::string _operator;
  int _operatorType;
  int _operatorNumber;
  std::list<std::string> _procedures;

  void _tokenizeParenContent(std::string &parenContent);
  void _tokenizeIterator(std::string rawIterator);
  void _tokenizeCondition(std::string rawCondition);
  void _tokenizeOperator(std::string rawOperator);
  void _tokenizeBracketContent(std::string &bracketContent);
};

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
  unsigned bracketLen = file.find("}") - openBracket;

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
      _condition = token;
      // _tokenizeCondition(token);
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

  int conditionLength = 1;
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

  default:
    break;
  }

  rawCondition = rawCondition.substr(conditionLength,
                                     rawCondition.length() - conditionLength);

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
  std::cout
      << "==========[ Loop ]==========" << std::endl
      << "Iterator: " << _iterator << std::endl
      << "Intial Counter Number: " << _counterNumber << std::endl
      << "Intial Counter Var: " << _counterVar << std::endl
      << "Condition: " << _condition
      << std::endl
      // << "Condition Type: " << getConditionRepresentation(_conditionType)
      // << std::endl
      // << "Condition Number: " << _conditionNumber << std::endl
      // << "Condition Var: " << _conditionVar << std::endl
      << "Operator: " << (_operator.empty() ? "Empty" : _operator) << std::endl
      << std::endl
      << "Procedures: " << std::endl;

  for (auto &i : _procedures) {
    std::cout << i << std::endl;
  }

  std::cout << std::endl;
}

int main() {

  // Opening File
  std::string fileName;
  std::cout << "Enter the name of the input file" << std::endl;
  std::cin >> fileName;
  std::ifstream input(fileName);

  // Creating string from file;
  std::list<std::string> loopHolder;
  readFile(input, loopHolder);
  tokenizeLoops(loopHolder);
  return 0;
}

// Reads the file and appends it to a string. Making it one line for easier
// tokenizing
void readFile(std::ifstream &input, std::list<std::string> &loopHolder) {
  std::string fileContent;
  int forCounter = 0;
  int foundFor = false;
  if (input.is_open()) {

    // Creating the buffer string
    std::string lines;

    // Reading each line
    while (getline(input, lines)) {
      if (lines.find("for") != std::string::npos) {
        foundFor = true;
        forCounter++;
      }
      if (foundFor) {
        if (forCounter > 0) {
          lines.erase(std::remove(lines.begin(), lines.end(), '\r'),
                      lines.end());
          fileContent.append(lines);
        }
        if (lines.find("}") != std::string::npos) {
          forCounter--;
        }
        if (forCounter == 0) {
          foundFor = false;
          fileContent.erase(
              std::remove(fileContent.begin(), fileContent.end(), ' '),
              fileContent.end());
          loopHolder.push_back(fileContent);
          fileContent.clear();
        }
      }
    }
  }
}

void tokenizeLoops(std::list<std::string> &loopHolder) {
  for (auto &i : loopHolder) {
    Loop *holder = new Loop();
    holder->tokenize(i);
    holder->printMembers();
    delete (holder);
  }
}

// Checking if entire string is a number. From
// https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
bool isNumber(std::string &s) {
  return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}
