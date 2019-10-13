#include "packet.hpp"
#include "poem.hpp"
#include <algorithm>
#include <fstream>
#include <list>
#include <string>

void readFile(std::ifstream &, std::list<Poem> &);

int main() {
  std::string fileName;
  std::cin >> fileName;
  std::ifstream input(fileName);
  std::list<Poem> poems;
  readFile(input, poems);
  for (auto &i : poems) {
    i.print();
  }

  return 0;
}

void readFile(std::ifstream &input, std::list<Poem> &poems) {
  std::string fileContent;
  if (input.is_open()) {

    // Creating buffer string
    std::string lines;

    while (getline(input, lines)) {

      // Deleting carriage return to fix segfault error when running the code on
      // unix machines with dos input
      lines.erase(std::remove(lines.begin(), lines.end(), '\r'), lines.end());

      // Creating temp packet and flag
      Packet tempPacket(lines);
      bool isAppended = false;

      // Checking if poem is already in the list
      for (auto &i : poems) {
        if (i.isSame(tempPacket)) {
          i.append(tempPacket);
          isAppended = true;
          break;
        }
      }

      // If not in the list, create new poem
      if (!isAppended) {
        Poem newPoem(tempPacket);
        poems.push_back(newPoem);
      }
    }
  }
}
