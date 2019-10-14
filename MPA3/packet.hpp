#ifndef MPA3_PACKET
#define MPA3_PACKET

#include <bitset>
#include <iostream>
#include <list>
#include <string>

class Packet {

private:
  // Stores all fields
  std::string _rawPacket;
  std::string _sourceAddress;
  std::string _destinationAddress;
  int _sequenceNumber;
  std::bitset<17> _checksum;
  unsigned int _lengthOfData;
  std::string _data;

  // Handle caveats
  bool _isChecksumPassing;

  // Tokenize packet
  bool _tokenize();
  bool _tokenizeAddress(const bool &, std::string &);
  bool _tokenizeSequenceNumber(std::string &);
  bool _tokenizeChecksum(std::string &);
  bool _tokenizeLengthOfData(std::string &);
  bool _tokenizeData(std::string &);

  // Compute Checksum
  void _computeChecksum();

  std::string _twosComplement(std::string &);

public:
  // Constructors
  Packet(const std::string &);

  // Getters
  std::string sourceAddress() const;
  std::string destinationAddress() const;
  int sequenceNumber() const;

  std::string data() const;
};

#endif
