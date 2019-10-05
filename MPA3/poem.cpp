#include "poem.hpp"

void Poem::_sort() {
  for (std::list<Packet>::iterator i = _packets.begin(); i != _packets.end();
       ++i) {
    for (std::list<Packet>::iterator j = i; j != _packets.end(); ++j) {
      if (*i.getSequenceNumber() < *j.getSequenceNumber()) {
      }
    }
  }
}

void Poem::append(Packet &inputPacket) {
  if (_packets.empty()) {
    _sourceAddress = inputPacket.getSourceAddress();
    _destinationAddress = inputPacket.getDestinationAddress();
  }

  _packets.push_back(inputPacket);
}

void Poem::print() {

  // Sort before printing
  _sort();

  bool isFirst = true;
  for (auto &packet : _packets) {
    packet.print();

    // If it is the first in the list then it is the title. The following line
    // needs to be the source address and destination address
    if (isFirst) {
      std::cout << _sourceAddress << "/" << _destinationAddress << std::endl;
      isFirst = false;
    }
  }
}

bool Poem::isSame(std::string &sourceAddress, std::string &destinationAddress) {
  return _sourceAddress == sourceAddress &&
         _destinationAddress == destinationAddress;
}
