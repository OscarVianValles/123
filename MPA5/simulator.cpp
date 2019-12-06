#include "simulator.hpp"

// Gets the current path by going to the parents iteratively
std::string Simulator::currentPath() {
  Node *curr = t->current();
  std::string path;
  while (curr) {
    path.insert(0, curr->content.name() + "/");
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
    } else if (inputString == ">") {
      c = new touch(tokens);
    } else if (inputString == ">>" || inputString == "edit") {
      c = new append(tokens);
    } else if (inputString == "cd") {
      c = new cd(tokens);
    } else if (inputString == "rn") {
      c = new rn(tokens);
    } else if (inputString == "show") {
      c = new show(tokens);
    } else if (inputString == "rm") {
      c = new rm(tokens);
    } else if (inputString == "rmdir") {
      c = new rmdir(tokens);
    } else if (inputString == "cp") {
      c = new cp(tokens);
    }

    // If c exists, execute it then deletes it
    if (c) {
      if (!c->execute(*(t))) {
        std::cout << "An error has occured" << std::endl;
      }
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
