#ifndef MPA3_POEM
#define MPA3_POEM

#include "packet.hpp"
#include <cmath>
#include <fstream>
#include <list>
#include <string>

class Poem {
private:
  std::string _sourceAddress;
  std::string _destinationAddress;
  std::list<Packet> _packets;

  void _tidy();
  bool _packetCompare(const Packet &, const Packet &);

public:
  Poem(Packet);
  void append(Packet &);
  void print(std::ofstream &);
  bool isSame(const Packet &packet);
};

#endif
