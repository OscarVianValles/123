#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>

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

// Creating Loop Class
class Loop {

public:
  std::string getIterator();
  std::string getCondition();
  std::string getOperator();
  std::string getProcedures();

  void tokenize(std::string &file);
  void printMembers();

private:
  std::string _iterator;
  int _counter;
  int _conditionType;
  int _conditionNumber;
  int _operatorType;
  int _operatorNumber;
  std::list<std::string> _procedures;

  void _tokenizeParenContent(std::string &parenContent);
  void _tokenizeIterator(std::string rawIterator);
  void _tokenizeCondition(std::string rawCondition);
  void _tokenizeOperator(std::string rawOperator);
  void _tokenizeBracketContent(std::string &bracketContent);
};

void Loop::tokenize(std::string &file) {
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
      _counter = stoi(token);
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

  _conditionNumber = stoi(rawCondition);
}

void Loop::_tokenizeOperator(std::string rawOperator) {
  rawOperator = rawOperator.substr(_iterator.length(),
                                   rawOperator.length() - _iterator.length());
}

void Loop::_tokenizeBracketContent(std::string &bracketContent) {
  // Creating buffer variables
  std::istringstream tempStream(bracketContent);
  std::string token;

  while (std::getline(tempStream, token, ';')) {
    _procedures.push_back(token);
  }
}

void Loop::printMembers() {
  std::cout << "Iterator: " << _iterator << std::endl
            << "Intial Counter: " << _counter << std::endl
            << "Condition Type: " << getConditionRepresentation(_conditionType)
            << std::endl
            << "Condition Number: " << _conditionNumber << std::endl
            << "Operator Number: "
            << (_operatorNumber == 0 ? "Empty"
                                     : std::to_string(_operatorNumber))
            << std::endl
            << std::endl
            << "Procedures: " << std::endl;

  for (auto &i : _procedures) {
    std::cout << i << std::endl;
  }
}

std::string readFile(std::ifstream &input);
int main() {

  // Opening File
  std::string fileName = "inputFile.txt";
  std::ifstream input(fileName);

  // Creating string from file;
  std::string file;
  file = readFile(input);

  Loop *first = new Loop();

  first->tokenize(file);
  first->printMembers();

  return 0;
}

// Reads the file and appends it to a string. Making it one line for easier
// tokenizing
std::string readFile(std::ifstream &input) {

  // Creating the string to receive the contents of the file
  std::string fileContent;
  if (input.is_open()) {

    // Creating the buffer string
    std::string lines;

    // Reading each line
    while (getline(input, lines)) {

      // Appending each line to the string to be returned
      fileContent.append(lines);
    }
  }

  // Removing Spaces
  fileContent.erase(std::remove(fileContent.begin(), fileContent.end(), ' '),
                    fileContent.end());

  return fileContent;
}
