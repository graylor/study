#ifndef HUFFMAN_TREE
#define HUFFMAN_TREE

#include <vector>
#include <queue>
#include "huffman.h"

class HuffmanTree {
public:
	HuffmanTree(const uint32_t* frequencies);
	~HuffmanTree();

	//Encoding
	void putByte(BYTE byte);
	bool hasNextBit()const;
	unsigned char getNextBit();

	//Decoding
	//if return value is true, than we can getNextByte()
	bool putNextBit(unsigned char bit);
	BYTE getNextByte();

private:
	struct Node {
		const BYTE value_;
		const uint32_t frequency_;
		const Node* const left_;
		const Node* const right_;
		Node(BYTE value, uint32_t frequency, const Node* const node1 = NULL, const Node* const node2 = NULL);
		~Node();
	private:
		Node(const Node&);
		void operator=(const Node&);
	};
	struct PointerComparator {
		bool operator()(const Node* node1, const Node* node2) const {
			return node1->frequency_ > node2->frequency_;
		}
	};

	void buildHuffmanCodes(const Node* const current, std::vector<bool>& currentCode);
	HuffmanTree(const HuffmanTree&);
	void operator=(const HuffmanTree&);

	const Node* root_;
	const Node* currentNode_;
	std::vector<bool>::iterator currentCodeIterator_;
	std::vector<bool>::iterator currentCodeEnd_;
	std::vector< std::vector<bool> > codes_;
};

#endif
