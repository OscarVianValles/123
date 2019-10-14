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

void Poem::print(std::ofstream &output) {

  // Sort and remove duplicates before printing
  _tidy();

  unsigned int expectedSequence = 0;
  for (auto &packet : _packets) {

    // Hold sequenceNumber so that the function will not be called twice
    int actualSequence = packet.sequenceNumber();
    unsigned int absActualSequence = std::abs(actualSequence);

    // checks if the expected sequence number is the same as the actual sequence
    // number. if it isn't then it prints the special lines and loops until the
    // expectedSequence is the same as the actual sequence
    while (absActualSequence != expectedSequence) {
      if (expectedSequence == 0) {
        output << "[title missing]" << std::endl;
        output << _sourceAddress << "/" << _destinationAddress << std::endl;
      } else {
        output << "[line missing]" << std::endl;
      }

      // Increment the expected sequence because the expected sequence has
      // already been determined that it does not exist
      expectedSequence++;
    }

    output << packet.data() << std::endl;

    // If it is the first in the list then it is the title. The following line
    // needs to be the source address and destination address
    if (expectedSequence == 0) {
      output << _sourceAddress << "/" << _destinationAddress << std::endl;
    }

    // If a negative sequence number is found then the peom has ended
    if (actualSequence < 0) {
      break;
    }

    expectedSequence++;
  }
}

// Receives a packet to compare if the packet is part of the current poem
bool Poem::isSame(const Packet &packet) {
  return _sourceAddress == packet.sourceAddress() &&
         _destinationAddress == packet.destinationAddress();
}
