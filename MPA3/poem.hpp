#ifndef MPA3_POEM
#define MPA3_POEM

#include "packet.hpp"
#include <list>
#include <string>

class Poem {
private:
  std::string _sourceAddress;
  std::string _destinationAddress;
  std::list<Packet> _packets;

  void _sort();

public:
  void append(Packet &);
  void print();
  bool isSame(std::string &, std::string &);
};

#endif
