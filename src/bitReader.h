#ifndef BIT_READER
#define BIT_READER

#include "huffman.h"

class BitReader {
public:
	BitReader(const std::string& fileName);
	~BitReader();
	bool readBit();
	uint32_t readNumber();
	bool eof() const;
	bool is_open() const;
	bool close();
private:
	BYTE bufferByte_;
	size_t positionInByte_;
	std::ifstream inFile_;

	BitReader(const BitReader&);
	void operator=(const BitReader&);
};

#endif
