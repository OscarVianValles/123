#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// Creating Loop class

class Loop {
public:
  std::string getIdentifier();
  std::string getCondition();
  std::string getOperator();
  std::string getProcedures();

  void tokenize(std::string file);
  void printMembers();

private:
  std::string identifier;
  std::string condition;
  std::string loopOperator; // Operator is a reserved word
  std::string procedures;
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

  return fileContent;
}
