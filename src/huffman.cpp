#include "huffman.h"
#include "huffmanTree.h"
#include "bitWriter.h"
#include "bitReader.h"

void encode(const std::string& originFile, const std::string& destFile) {
	std::ifstream inputFile(originFile.c_str(), std::ios::binary | std::ios::in);
	if(!inputFile.is_open()) {
		std::cerr << "Can't open file " << originFile << std::endl;
		return;
	}
	
	//Building huffman tree
	uint32_t frequencies[ALPHABET_SIZE];
	std::fill(frequencies, frequencies + ALPHABET_SIZE, 0);
	unsigned char currentChar = 0;
	uint32_t totalBytes = 0;
	while(inputFile.read((char *) &currentChar, 1)) {
		frequencies[currentChar] += 1;
		++totalBytes;
	}
	HuffmanTree tree(frequencies);
	
	//Writing archive file
	inputFile.clear();
	inputFile.seekg(inputFile.beg);
	BitWriter outputFile(destFile.c_str());
	//Number of bytes in file
	outputFile.writeNumber(totalBytes);
	//Frequency table
	for(size_t i = 0; i != ALPHABET_SIZE; ++i) {
		outputFile.writeNumber(frequencies[i]);
	}
	//Writing data
	while(inputFile.read((char *) &currentChar, 1)) {
		tree.putByte(currentChar);
		while(tree.hasNextBit()) {
			outputFile.writeBit(tree.getNextBit());
		}
	}
}

void decode(const std::string& originFile, const std::string& destFile) {
	BitReader archive(originFile.c_str());
	if(!archive.is_open()) {
		std::cerr << "Can't open file " << originFile << std::endl;
		return;
	}

	//Reading header
	uint32_t numberOfBytes = archive.readNumber();
	uint32_t frequencies[ALPHABET_SIZE];
	for(size_t i = 0; i != ALPHABET_SIZE; ++i) {
		frequencies[i] = archive.readNumber();
	}
	//Build huffman tree
	HuffmanTree tree(frequencies);

	//Write decompressed file
	std::ofstream decompFile(destFile.c_str(), std::ios::binary | std::ios::out);
	for(uint32_t i = 0; i != numberOfBytes; ++i) {
		while(!tree.putNextBit(archive.readBit()));
		decompFile.put(tree.getNextByte());
	}
}

int main(int argc, char** argv) {
	if(argc < 6) {
		std::cerr << "Wrong usage" << std::endl;
		return -1;
	}
	std::string originFile;
	std::string destFile;
	enum {UNDEFINED, DECODE, ENCODE} purpose = UNDEFINED;
	for(size_t i = 1; i < (size_t)argc; ++i) {
		if(std::string(argv[i]) == "-i") {
			originFile = argv[++i];
		} else if(std::string(argv[i]) == "-o") {
			destFile = argv[++i];
		} else if(std::string(argv[i]) == "-c") {
			purpose = ENCODE;
		} else if(std::string(argv[i]) == "-d") {
			purpose = DECODE;
		}
	}
	if(UNDEFINED == purpose) {
		std::cerr << "Wrong usage" << std::endl;
		return -1;
	}
	if(DECODE == purpose)
		decode(originFile, destFile);
	if(ENCODE == purpose)
		encode(originFile, destFile);
	return 0;
}
