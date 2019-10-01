#include "packet.hpp"

Packet::Packet(const std::string &inputString) : _rawPacket(inputString) {
  _tokenize();
}

Packet::Packet(const bool &isMissing) { _isMissing = isMissing; }

bool Packet::_tokenize() {

  // Initial field size is 32 as the source address is 32 bits
  int fieldSize = 32;

  // Creates a copy of the string to save the original packet for checksum
  // algorithm
  std::string packetCopy = _rawPacket;

  /* +--------------------------+ *
   * | i | Definition           | *
   * |---+----------------------| *
   * | 0 | Source Address       | *
   * | 1 | Destination Address  | *
   * | 2 | Sequence Number      | *
   * | 3 | Checksum             | *
   * | 4 | Length of Data       | *
   * | 5 | Data                 | *
   * +--------------------------+ */
  for (int i = 0; i < 6; i++) {

    // Creates the current string to be tokenized from the copy
    std::string currString = packetCopy.substr(0, fieldSize);

    // Deletes currString from packetCopy for the next iteration
    packetCopy.erase(0, fieldSize);

    // Refer to table above for description about the cases
    switch (i) {
    case 0:
    case 1:
      _tokenizeAddress(i == 0 ? true : false, currString);
      break;

    case 2:
      _tokenizeSequenceNumber(currString);
      break;

    case 3:
      _tokenizeChecksum(currString);
      break;

    case 4:
      _tokenizeLengthOfData(currString);
      break;

    case 5:
      _tokenizeData(currString);
      break;
    }

    // If Destination address is done, field size is 16 as the following fields
    // have a field size of 16
    if (i == 1) {
      fieldSize = 16;
    }

    // Except if the next field is the data. _lengthOfData is obtained before
    // reaching here
    else if (i == 4) {
      fieldSize = _lengthOfData;
    }
  }

  return true;
}

bool Packet::_tokenizeAddress(const bool &isSource, std::string &inputString) {

  // Creates a reference to either the source address or the destination address
  std::string &addressRef = isSource ? _sourceAddress : _destinationAddress;

  for (int i = 0; i < 4; i++) {

    // std::stoull converts a string to an unsigned long long. It accepts the
    // string, a pointer to the next position after converting, which I do not
    // use, and the base to convert from. This is then converted to a a string
    addressRef.append(
        std::to_string(std::stoull(inputString.substr(0, 8), nullptr, 2)));

    // Deletes part of the input string that was already tokenized
    inputString.erase(0, 8);

    // Appends a . after the number, unless it is the last number
    if (i != 3) {
      addressRef.append(".");
    }
  }

  return true;
}

bool Packet::_tokenizeSequenceNumber(std::string &inputString) {
  _sequenceNumber = std::stoull(inputString, nullptr, 2);
  return true;
}

// TODO
bool Packet::_tokenizeChecksum(std::string &inputString) {
  std::cout << inputString.length() << std::endl;
  return true;
}

bool Packet::_tokenizeLengthOfData(std::string &inputString) {
  _lengthOfData = std::stoull(inputString, nullptr, 2);
  return true;
}

// TODO
bool Packet::_tokenizeData(std::string &inputString) {
  std::cout << inputString.length() << std::endl;
  return true;
}
