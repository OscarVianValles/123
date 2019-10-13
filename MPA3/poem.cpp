#include "poem.hpp"

bool packetCompare(const Packet &first, const Packet &second) {
  return first.sequenceNumber() < second.sequenceNumber();
}

Poem::Poem(Packet initial) { append(initial); }

void Poem::_sort() { _packets.sort(packetCompare); }

void Poem::append(Packet &inputPacket) {
  if (_packets.empty()) {
    _sourceAddress = inputPacket.sourceAddress();
    _destinationAddress = inputPacket.destinationAddress();
  }

  _packets.push_back(inputPacket);
}

void Poem::print() {

  // Sort before printing
  _sort();

  // Delete last packet. Usually is garbage data
  _packets.pop_back();

  unsigned int expectedSequence = 0;
  for (auto &packet : _packets) {
    if (packet.sequenceNumber() != expectedSequence) {
      if (expectedSequence == 0) {
        std::cout << "[title missing]" << std::endl;
        std::cout << _sourceAddress << "/" << _destinationAddress << std::endl;
      } else {
        std::cout << "[line missing]" << std::endl;
      }

      expectedSequence++;
    } else {
      packet.print();
    }

    // If it is the first in the list then it is the title. The following line
    // needs to be the source address and destination address
    if (expectedSequence == 0) {
      std::cout << _sourceAddress << "/" << _destinationAddress << std::endl;
    }

    expectedSequence++;
  }

  // Print separator
  std::cout << std::endl
            << "---------------------------------------------------------------"
               "-----------------"
            << std::endl
            << std::endl;
}
bool Poem::isSame(const Packet &packet) {
  return _sourceAddress == packet.sourceAddress() &&
         _destinationAddress == packet.destinationAddress();
}
