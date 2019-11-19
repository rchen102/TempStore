#include "../include/FullyAssociative.h"
#include <iostream>

/****** FullyAssociative ******/
FullyAssociative::FullyAssociative(int blockSize, int cacheSize, int mode) {
	this->blockSize = blockSize;
	this->cacheSize = 1024 * cacheSize;
	this->blockNum = this->cacheSize / this->blockSize;

	this->hit = 0;
	this->access = 0;

	this->mode = 0;
	if (mode == 0) {
		this->LRUcache = new LRU(this->blockNum);
	}
}

FullyAssociative::~FullyAssociative() {
	if (this->mode == 0) {
		delete this->LRUcache;
	}
}

void FullyAssociative::processOne(string behavior, unsigned long long addr) {
	this->access++;
	int blockAddr = this->addrToBlockAddr(addr);
	if (this->mode == 0) {
		if (this->LRUcache->access(blockAddr) == 1) this->hit++;
	}
}

int FullyAssociative::addrToBlockAddr(unsigned long long addr) {
	int blockAddr = addr / this->blockSize;
	return blockAddr;
}