#ifndef MPA3_PACKET
#define MPA3_PACKET

#include <bitset>
#include <iostream>
#include <list>
#include <string>

class Packet {

private:
  std::string _rawPacket;
  std::string _sourceAddress;
  std::string _destinationAddress;
  unsigned int _sequenceNumber;
  std::bitset<17> _checksum;
  unsigned int _lengthOfData;
  std::string _data;

  bool _isMissing;

  bool _tokenize();
  bool _tokenizeAddress(const bool &, std::string &);
  bool _tokenizeSequenceNumber(std::string &);
  bool _tokenizeChecksum(std::string &);
  bool _tokenizeLengthOfData(std::string &);
  bool _tokenizeData(std::string &);
  bool _computeChecksum();

public:
  Packet(const std::string &);
  Packet(const bool &);
  std::string getSourceAddress() const;
  std::string getDestinationAddress() const;
  unsigned int getSequenceNumber() const;
};

#endif
