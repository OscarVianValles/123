#ifndef MPA5_HELPERS
#define MPA5_HELPERS

#include <list>
#include <sstream>
#include <string>
extern std::list<std::string> tokenize(std::string, char);

extern void replaceAll(std::string &source, const std::string &from,
                       const std::string &to);
#endif
