#include "cd.hpp"

cd::cd(std::list<std::string> inputParams) { params = inputParams; }

cd::~cd() {}

bool cd::execute(FileTree &t) {
  if (params.empty()) {
    std::cout << "cd: missing file operand" << std::endl;
    return false;
  }

  std::string inputString = params.front();

  if (inputString == "..") {
    if (t.current()->parent != nullptr) {
      t.changeCurrent(t.current()->parent);
      return true;
    } else {
      return false;
    }
  } else {
    t.changeCurrent(t.search(inputString, false));
    return true;
  }
}
