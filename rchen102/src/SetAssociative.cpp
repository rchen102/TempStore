#include "../include/SetAssociative.h"
#include <iostream>

using std::cout;
using std::endl;

/****** SetAssociative ******/
SetAssociative::SetAssociative(int blockSize, int cacheSize, int associativity) {
	this->blockSize = blockSize;
	this->cacheSize = 1024 * cacheSize;
	this->blockNum = this->cacheSize / this->blockSize;

	this->setNum = this->blockNum / associativity;

	this->hit = 0;
	this->access = 0;

	this->cache = new LRU* [this->setNum];
	for (int i = 0; i < this->setNum; i++) {
		this->cache[i] = new LRU(associativity);
	}
}

SetAssociative::~SetAssociative() {
	for (int i = 0; i < this->setNum; i++) {
		delete this->cache[i];
	}
	delete[] this->cache;
}

void SetAssociative::processOne(string behavior, unsigned long long addr) {
	this->access++;
	int blockIdx = this->addrToBlockIndex(addr);
	int setNum = blockIdx % this->setNum;

	if (this->cache[setNum]->access(blockIdx) == 1) this->hit++;
}

int SetAssociative::addrToBlockIndex(unsigned long long addr) {
	int blockIdx = addr / this->blockSize;
	return blockIdx;
}

/****** SetAssociativeSet ******/
SetAssociativeSet::SetAssociativeSet() {
	this->sa1 = new SetAssociative(32, 16, 2);
	this->sa2 = new SetAssociative(32, 16, 4);
	this->sa3 = new SetAssociative(32, 16, 8);
	this->sa4 = new SetAssociative(32, 16, 16);
}

SetAssociativeSet::~SetAssociativeSet() {
	delete this->sa1;
	delete this->sa2;
	delete this->sa3;
	delete this->sa4;
}

void SetAssociativeSet::processOne(string behavior, unsigned long long addr) {
	this->sa1->processOne(behavior, addr);
	this->sa2->processOne(behavior, addr);
	this->sa3->processOne(behavior, addr);
	this->sa4->processOne(behavior, addr);
}

void SetAssociativeSet::printRes() {
	cout << this->sa1->getHit() << "," << this->sa1->getAccess() << "; "
		 << this->sa2->getHit() << "," << this->sa2->getAccess() << "; "
		 << this->sa3->getHit() << "," << this->sa3->getAccess() << "; "
		 << this->sa4->getHit() << "," << this->sa4->getAccess() << ";" << endl;
}