#include "poem.hpp"

// Binary predicate for list::sort
bool packetCompare(const Packet &first, const Packet &second) {
  return std::abs(first.sequenceNumber()) < std::abs(second.sequenceNumber());
}

// Binary predicate for list::unique
bool packetDuplicate(const Packet &first, const Packet &second) {
  return first.sequenceNumber() == second.sequenceNumber();
}

// Constructor. Poems are always created with an initial packet
Poem::Poem(Packet initial) { append(initial); }

// Tidies up the poem by sorting depending on the sequence number and removing
// duplicates
void Poem::_tidy() {
  _packets.sort(packetCompare);

  // list::unique removes the duplicates depending on the return value of the
  // binary predicate
  _packets.unique(packetDuplicate);
}

// Appends a packet to the poem. does not care if it will append to the back in
// the wrong order
void Poem::append(Packet &inputPacket) {

  // If this is the first packet to be appended, the source address and
  // destination address is copied from the packet to give the poem its identity
  if (_packets.empty()) {
    _sourceAddress = inputPacket.sourceAddress();
    _destinationAddress = inputPacket.destinationAddress();
  }

  _packets.push_back(inputPacket);
}

void Poem::print() {

  // Sort and remove duplicates before printing
  _tidy();

  // Delete last packet. Usually is garbage data
  _packets.pop_back();

  int expectedSequence = 0;
  for (auto &packet : _packets) {

    // Hold sequenceNumber so that the function will not be called twice
    int actualSequence = packet.sequenceNumber();

    // checks if the expected sequence number is the same as the actual sequence
    // number. if it isn't then it prints the special lines
    if (std::abs(actualSequence) != expectedSequence) {
      if (expectedSequence == 0) {
        std::cout << "[title missing]" << std::endl;
        std::cout << _sourceAddress << "/" << _destinationAddress << std::endl;
      } else {
        std::cout << "[line missing]" << std::endl;
      }

      // Increment the expected sequence because the expected sequence has
      // already been determined that it does not exist
      expectedSequence++;
    } else {
      packet.print();
    }

    // If it is the first in the list then it is the title. The following line
    // needs to be the source address and destination address
    if (expectedSequence == 0) {
      std::cout << _sourceAddress << "/" << _destinationAddress << std::endl;
    }

    if (actualSequence < 0) {
      break;
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

// Receives a packet to compare if the packet is part of the current poem
bool Poem::isSame(const Packet &packet) {
  return _sourceAddress == packet.sourceAddress() &&
         _destinationAddress == packet.destinationAddress();
}
