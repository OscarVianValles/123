#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>

#include "coordinates.hpp"
#include "mazesolver.hpp"
void readFile(std::ifstream &, std::queue<Maze> &);

int main() {
  // Open File and create mazes
  // std::string fileName;
  // std::cin >> fileName;
  std::ifstream input("maze.in");
  std::queue<Maze> mazes;
  readFile(input, mazes);

  // Create output file

  std::ofstream output("maze.out");

  // Solve each maze and write to file
  while (!mazes.empty()) {
    MazeSolver<std::queue<Cell>> a(mazes.front());
    a.solve();
    output << a.solution() << std::endl;

    MazeSolver<std::stack<Cell>> b(mazes.front());
    b.solve();
    output << b.solution() << std::endl;
    mazes.pop();
  }
  return 0;
}

void readFile(std::ifstream &input, std::queue<Maze> &mazes) {
  std::string fileContent;
  if (input.is_open()) {

    // Creating buffer string
    std::string lines;

    int counter = -1;
    bool first = true;

    std::string maze;
    Coordinates dimensions;

    while (getline(input, lines)) {
      if (counter != -1) {
        // Deleting carriage return to fix segfault error when running the code
        // on unix machines with dos input
        lines.erase(std::remove(lines.begin(), lines.end(), '\r'), lines.end());

        // Getting dimensions and adding maze to the queue
        if (counter == 0) {

          // Does not create a maze if this is the first time that this block of
          // code is run because no maze has been parsed yet
          if (!first) {
            mazes.push(Maze(maze, dimensions));
          }

          maze.clear();

          // Create temporary string streams and strings to tokenize the
          // dimensions
          std::istringstream tempStream(lines);
          std::string token;

          // Tokenize dimensions
          int tokenizingCounter = 0;
          while (std::getline(tempStream, token, ' ')) {
            if (tokenizingCounter == 0) {
              dimensions.y = counter = stoi(token);
            } else {
              dimensions.x = stoi(token);
            }

            tokenizingCounter++;
          }

          first = false;
        } else {
          // Appending maze to the temporary string
          maze.append(lines);
          counter--;
        }
      } else {
        // Skip number of test cases
        counter++;
      }
    }

    // Handle last maze
    mazes.push(Maze(maze, dimensions));
  }
}
