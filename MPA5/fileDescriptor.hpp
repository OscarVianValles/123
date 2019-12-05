#ifndef MPA5_FILE_DESCRIPTOR
#define MPA5_FILE_DESCRIPTOR

#include <ctime>
#include <string>

class Descriptor {
private:
  bool __isFile;
  time_t __modified;
  time_t __created;
  std::string __name;
  std::string __fileContent;

public:
  // Constructor
  Descriptor(bool, std::string);
  Descriptor(bool, std::string, std::string);

  // Builders
  bool isFile();
  bool isFolder();
  time_t created();
  time_t modfied();
  std::string name();
  std::string fileContent();

  void changeName(std::string);
  void appendFileContent(std::string);
  void modify();
};

#endif
