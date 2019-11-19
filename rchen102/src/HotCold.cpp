#include "../include/HotCold.h"

#include <cstring>
#include <iostream>

using std::cout;
using std::endl;

HotCold::HotCold(int capacity) {
	this->capacity = capacity;

	this->cache = new int[capacity];
	memset(this->cache, -1, sizeof(int) * capacity);  // initialize to -1

	/*
	 * Initialize to 0
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
 * 1 for hit
 * -1 for miss
 */
int HotCold::access(int blockAddr) {
	for (int i = 0; i < this->capacity; i++) {
		if (this->cache[i] == blockAddr) {  
			// Hit    
			this->updateTreeWithHit(i);
			return 1;
		}
	}
	// Miss
	this->updateTreeWithMiss(blockAddr);
	return -1;
}


/* 
 * Update hotcold bit from bottom to top
 */
void HotCold::updateTreeWithHit(int blockIdx) {   
	// transfer block index to tree index
	int treeIdx = blockIdx + this->capacity - 1; 
	while (treeIdx != 0) {
		if (treeIdx % 2 == 0) {               // this is a right child 
			int parent = (treeIdx - 2) / 2;   // right = 2 * parent + 2
			this->tree[parent] = 1;           // left is cold
			treeIdx = parent;
		}
		else {                                // this is a left child 
			int parent = (treeIdx - 1) / 2;   // left = 2 * parent + 1
			this->tree[parent] = 0;           // right is cold
			treeIdx = parent;
		}
	}
}

/* 
 * Select victim and update hotcold bit from top to bottom
 */
void HotCold::updateTreeWithMiss(int blockAddr) {  
	int treeIdx = 0;
	while (treeIdx <= this->capacity-2) {
		if (this->tree[treeIdx] == 0) {       // right child is cold
			this->tree[treeIdx] = 1;          // after select victim and insert new data, it will become hot
			treeIdx = 2 * treeIdx + 2;        // right = 2 * parent + 2
		}
		else {                                // left child is cold
			this->tree[treeIdx] = 0;          // after select victim and insert new data, it will become hot
			treeIdx = 2 * treeIdx + 1;
		}
	}
	// transfer tree index to block index
	int blockIdx = treeIdx - this->capacity + 1;
	this->cache[blockIdx] = blockAddr;
}