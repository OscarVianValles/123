#include "fileDescriptor.hpp"

Descriptor::Descriptor(bool isFile, std::string name) {
  __isFile = isFile;
  __created = time(NULL);
  __modified = __created;
  __name = name;
}

Descriptor::Descriptor(bool isFile, std::string name, std::string fileContent) {
  __isFile = isFile;
  __created = time(NULL);
  __modified = __created;
  __name = name;
  __fileContent = fileContent;
}

bool Descriptor::isFile() { return __isFile; }

time_t Descriptor::created() { return __created; }

time_t Descriptor::modfied() { return __modified; }

std::string Descriptor::name() { return __name; }

std::string Descriptor::fileContent() { return __fileContent; }

void Descriptor::changeName(std::string x) {
  __name = x;
  __modified = time(NULL);
}

void Descriptor::appendFileContent(std::string x) {
  if (__isFile) {
    __fileContent += x;
    __modified = time(NULL);
  } else {
    throw 1;
  }
}

void Descriptor::modify() { __modified = time(NULL); }
