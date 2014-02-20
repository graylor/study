.PHONY: clean bin
CXX=g++
CXXFLAGS=-c -Wall -pedantic -std=c++11

all: bin/arj

bin/arj: bin/huffmanTree.o bin/huffman.o bin/bitWriter.o bin/bitReader.o bin
	$(CXX) bin/huffman.o bin/huffmanTree.o bin/bitWriter.o bin/bitReader.o -o bin/arj
bin/huffman.o: src/huffmanTree.h src/bitWriter.h src/bitReader.h src/huffman.h src/huffman.cpp bin
	$(CXX) $(CXXFLAGS) src/huffman.cpp -o bin/huffman.o
bin/huffmanTree.o: src/huffmanTree.cpp src/huffman.h bin
	$(CXX) $(CXXFLAGS) src/huffmanTree.cpp -o bin/huffmanTree.o
bin/bitWriter.o: src/bitWriter.cpp src/huffman.h bin
	$(CXX) $(CXXFLAGS) src/bitWriter.cpp -o bin/bitWriter.o
bin/bitReader.o: src/bitReader.cpp src/huffman.h bin
	$(CXX) $(CXXFLAGS) src/bitReader.cpp -o bin/bitReader.o
bin:
	mkdir -p bin
clean:
	rm -f bin/*.o bin/arj
