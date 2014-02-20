#include "bitWriter.h"

BitWriter::BitWriter(const std::string& fileName): 
		bufferByte_(0),
		positionInByte_(0),
		outFile_(fileName.c_str(), std::ios::binary | std::ios::out) {}

BitWriter::~BitWriter() {
	close();
}

bool BitWriter::writeBit(bool bit) {
	bufferByte_ = ((bufferByte_ << 1) | bit);
	if(CHAR_BIT == ++positionInByte_) {
		outFile_.write((char *) &bufferByte_, sizeof(bufferByte_));
		bufferByte_ = 0;
		positionInByte_ = 0;
	}
	return outFile_.good();
}

bool BitWriter::writeNumber(uint32_t positiveNumber) {
	for(size_t i = 0; i < sizeof(positiveNumber) * CHAR_BIT; ++i)
		writeBit((positiveNumber >> i) & 1);
	return outFile_.good();
}

bool BitWriter::close() {
	if(positionInByte_) {
		bufferByte_ = bufferByte_ << (CHAR_BIT - positionInByte_); 
		outFile_.write((char *) &bufferByte_, sizeof(bufferByte_));
	}
	outFile_.close();
	return outFile_.good();
}
