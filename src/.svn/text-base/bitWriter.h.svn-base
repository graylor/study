#ifndef BIT_WRITER
#define BIT_WRITER

#include "huffman.h"

class BitWriter {
public:
	BitWriter(const std::string& fileName);
	~BitWriter();
	bool writeBit(bool bit);
	bool writeNumber(uint32_t positiveNumber);
	bool close();
private:
	BYTE bufferByte_;
	size_t positionInByte_;
	std::ofstream outFile_;

	BitWriter(const BitWriter&);
	void operator=(const BitWriter&);
};

#endif
