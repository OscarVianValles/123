#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// Creating Loop class

class Loop {
public:
  std::string getIterator();
  std::string getCondition();
  std::string getOperator();
  std::string getProcedures();

  void tokenize(std::string &file);
  void tokenizeParenContent(std::string &parenContent);
  void tokenizeBracketContent(std::string &bracketContent);
  void printMembers();

private:
  std::string iterator;
  std::string condition;
  std::string loopOperator; // Operator is a reserved word
  std::string procedures;
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

  tokenizeParenContent(parenContent);
}

void Loop::tokenizeParenContent(std::string &parenContent) {

  // Creating buffer variables
  std::istringstream tempStream(parenContent);
  std::string token;
  int counter = 0;

  // Tokenizing the string
  while (std::getline(tempStream, token, ';')) {
    switch (counter) {
    case 0:
      iterator = token;
      break;
    case 1:
      condition = token;
      break;
    case 2:
      loopOperator = token;
      break;
    default:
      break;
    }

    counter++;
  }
}

void Loop::tokenizeBracketContent(std::string &bracketContent) {

  // Creating buffer variables
  std::istringstream tempStream(bracketContent);
  std::string token;
}

void Loop::printMembers() {
  std::cout << "Iterator: " << iterator << std::endl
            << "Condition: " << condition << std::endl
            << "Operator: " << (loopOperator.empty() ? "Empty" : loopOperator)
            << std::endl;
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
