#include "bitReader.h"

BitReader::BitReader(const std::string& fileName):
		bufferByte_(0),
		positionInByte_(0),
		inFile_(fileName.c_str(), std::ios::binary | std::ios::in) {}

BitReader::~BitReader() {
	close();
}

bool BitReader::readBit() {
	if(0 == positionInByte_) {
		inFile_.read((char *) &bufferByte_, sizeof(bufferByte_));
		positionInByte_ = 0;
	}
	bool result = 1 & (bufferByte_ >> (CHAR_BIT - 1 - positionInByte_));
	if(CHAR_BIT  == ++positionInByte_) { 
		positionInByte_ = 0;
	}
	return result;
}

uint32_t BitReader::readNumber() {
	uint32_t result = 0;
	for(size_t i = 0; i < sizeof(result) * CHAR_BIT; ++i)
		result |=  (readBit() << i);
	return result;
}

bool BitReader::eof() const {
	return inFile_.eof();
}

bool BitReader::close() {
	inFile_.close();
	return inFile_.good();
}

bool BitReader::is_open() const {
	return inFile_.is_open();
}
