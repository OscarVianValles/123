#include "simulator.hpp"

// Gets the current path by going to the parents iteratively
std::string Simulator::currentPath() {
  Node *curr = t->current();
  std::string path;
  while (curr) {
    path.insert(0, "/" + curr->content.name());
    curr = curr->parent;
  }

  return path;
}

// Constructor
Simulator::Simulator() { t = new FileTree(); }

// Deconstructor
Simulator::~Simulator() {
  delete t;
  t = nullptr;
}

void Simulator::execute() {
  // Create pointer to commands
  Command *c = nullptr;

  while (true) {
    // Print current path
    std::cout << currentPath() << " > ";

    // Holder string and get input with spaces
    std::string inputString;
    std::getline(std::cin, inputString);

    // If no input was passed, move to the next iteration
    if (inputString.empty()) {
      continue;
    }

    // Tokenize input to get command + params
    std::list<std::string> tokens = tokenize(inputString, ' ');

    // Get the command
    inputString = tokens.front();

    // Remove command so that the remaining tokens are params
    tokens.pop_front();

    // Commands
    if (inputString == "exit") {
      std::cout << "Bye!" << std::endl;
      break;
    } else if (inputString == "ls") {
      c = new ls(tokens);
    } else if (inputString == "mkdir") {
      c = new mkdir(tokens);
    } else if (inputString == "touch") {
      c = new touch(tokens);
    }

    // If c exists, execute it then deletes it
    if (c) {
      c->execute(*(t));
      delete c;
      c = nullptr;
    }
  }

  // Final Cleanup
  if (c) {
    delete c;
    c = nullptr;
  }
}
