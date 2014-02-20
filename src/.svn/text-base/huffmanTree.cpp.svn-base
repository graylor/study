#include "huffmanTree.h"

HuffmanTree::HuffmanTree(const uint32_t* frequencies):
		codes_(ALPHABET_SIZE){
	//Create terminal nodes
	std::priority_queue<Node*, std::vector<Node*>, PointerComparator> alphabetQueue;
	for(size_t i = 0; i != ALPHABET_SIZE; ++i) {
		if(frequencies[i] > 0) {
			alphabetQueue.push(new Node(i, frequencies[i]));
		}
	}
	
	//Special cases
	if(1 == alphabetQueue.size()) {
		root_ = new Node(0, 0, alphabetQueue.top());
		currentNode_ = root_;
		return;
	} else if(0 == alphabetQueue.size()) {
		root_ = NULL;
		currentNode_ = root_;
		return;
	}

	//Building huffman tree
	while(alphabetQueue.size() > 1) {
		Node* nodeFirst = alphabetQueue.top();
		alphabetQueue.pop();

		Node* nodeSecond = alphabetQueue.top();
		alphabetQueue.pop();

		alphabetQueue.push(new Node(0, nodeFirst->frequency_ + nodeSecond->frequency_, nodeFirst, nodeSecond));
	}
	root_ = alphabetQueue.top();
	currentNode_ = root_;

	//Calculate codes for bytes
	std::vector<bool> currentCode;
	buildHuffmanCodes(root_, currentCode); 
}

void HuffmanTree::buildHuffmanCodes(const Node* const current, std::vector<bool>& currentCode) {
	//If terminal node
	if(!current->left_ && !current->right_) {
		codes_[current->value_] = currentCode;
		return;
	}

	currentCode.push_back(0);
	buildHuffmanCodes(current->left_, currentCode);
	currentCode.pop_back();

	currentCode.push_back(1);
	buildHuffmanCodes(current->right_, currentCode);
	currentCode.pop_back();
}

HuffmanTree::~HuffmanTree() {
	delete root_;
}

void HuffmanTree::putByte(BYTE byte) {
	currentCodeIterator_ = codes_[byte].begin();
	currentCodeEnd_ = codes_[byte].end();
}

bool HuffmanTree::hasNextBit() const {
	return currentCodeIterator_ != currentCodeEnd_; 
}

unsigned char HuffmanTree::getNextBit() {
	return *(currentCodeIterator_++); 
}

bool HuffmanTree::putNextBit(unsigned char bit) {
	if(bit) 
		currentNode_ = currentNode_->right_;
	else 
		currentNode_ = currentNode_->left_;
	return !currentNode_->left_ && !currentNode_->right_;
}

BYTE HuffmanTree::getNextByte() {
	unsigned char byte = currentNode_->value_;
	currentNode_ = root_;
	return byte;
}

HuffmanTree::Node::Node(BYTE value, uint32_t frequency, const Node* const node1, const Node* const node2):
		value_(value),
		frequency_(frequency),
		left_(node1),
		right_(node2) {}

HuffmanTree::Node::~Node() {
	delete left_;
	delete right_;
}

