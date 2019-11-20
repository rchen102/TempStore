#include "../include/HotCold.h"

#include <cstring>

HotCold::HotCold(int capacity) {
	this->capacity = capacity;

	this->cache = new int[capacity];
	memset(this->cache, -1, sizeof(int) * capacity);  // initialize to -1

	/*
	 * Use tree to store hot/cold bits
	 * Initialize all bits to 0
	 * 0 -> right child is cold
	 * 1 -> left child is cold
	 */
	this->tree = new int[capacity-1]();   
}

HotCold::~HotCold() {
	delete[] this->cache;
	delete[] this->tree;
}

/*
 * Try to access data from cache
 * return 1 for hit; -1 for miss
 */
int HotCold::access(int blockAddr) {
	for (int i = 0; i < this->capacity; i++) {
		if (this->cache[i] == blockAddr) {   // Hit
			this->updateTreeWithHit(i);
			return 1;
		}
	}
	// Miss
	this->updateTreeWithMiss(blockAddr);
	return -1;
}


/* 
 * Do index transfer, then update hot/cold bit
 */
void HotCold::updateTreeWithHit(int blockIdx) {
	int treeIdx = blockIdx + this->capacity - 1;
	this->updateHotColdBit(treeIdx);
}

/* 
 * Select victim and update hot/cold bit
 */
void HotCold::updateTreeWithMiss(int blockAddr) {  
	int treeIdx = 0;
	while (treeIdx <= this->capacity-2) {
		if (this->tree[treeIdx] == 0) {       // right child is cold
			treeIdx = 2 * treeIdx + 2;        // right = 2 * parent + 2
		}
		else {                                // left child is cold
			treeIdx = 2 * treeIdx + 1;        // left = 2 * parent + 1
		}
	}
	// transfer tree index to block index
	int blockIdx = treeIdx - this->capacity + 1;
	this->cache[blockIdx] = blockAddr;
	this->updateHotColdBit(treeIdx);
}

/* 
 * Update hotcold bit of the tree from bottom to top
 */
void HotCold::updateHotColdBit(int treeIdx) {
	while (treeIdx != 0) {
		if (treeIdx % 2 == 0) {               // this is a right child 
			int parent = (treeIdx - 2) / 2;   // right = 2 * parent + 2
			this->tree[parent] = 1;           // left is cold, right is hot
			treeIdx = parent;
		}
		else {                                // this is a left child 
			int parent = (treeIdx - 1) / 2;   // left = 2 * parent + 1
			this->tree[parent] = 0;           // right is cold, left is hot
			treeIdx = parent;
		}
	}
}