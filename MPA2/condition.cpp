#include "condition.hpp"

void Condition::tokenize(std::string rawCondition, int iteratorLength) {
  rawCondition = rawCondition.substr(iteratorLength,
                                     rawCondition.length() - iteratorLength);

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

  default:
    break;
  }
}
}
