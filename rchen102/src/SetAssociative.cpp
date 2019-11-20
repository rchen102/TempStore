#include "../include/SetAssociative.h"
#include <iostream>

using std::cout;
using std::endl;

/****** SetAssociative ******/
SetAssociative::SetAssociative(int blockSize, int cacheSize, int associativity, int mode) {
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
	this->mode = mode;
}

SetAssociative::~SetAssociative() {
	for (int i = 0; i < this->setNum; i++) {
		delete this->cache[i];
	}
	delete[] this->cache;
}

void SetAssociative::processOne(string behavior, unsigned long long addr) {
	this->access++;
	int blockAddr = this->addrToBlockAddr(addr);   // transfer address to block address
	int setNum = blockAddr % this->setNum;         // get set number from block address

	if (this->mode == 0) {
		if (this->cache[setNum]->access(blockAddr) == 1) this->hit++;
	}
	else if (this->mode == 1) {
		if (this->cache[setNum]->access(blockAddr, behavior) == 1) this->hit++;
	}
	else if (this->mode == 2) {
		int nextBlockAddr = blockAddr + 1;
		int nextSetNum = nextBlockAddr % this->setNum;
		if (this->cache[setNum]->access(blockAddr) == 1) this->hit++;
		this->cache[nextSetNum]->access(nextBlockAddr);
	}
	else if (this->mode == 3) {
		if (this->cache[setNum]->access(blockAddr) == 1) this->hit++;
		else {
			int nextBlockAddr = blockAddr + 1;
			int nextSetNum = nextBlockAddr % this->setNum;
			this->cache[nextSetNum]->access(nextBlockAddr);
		}
	}
}

int SetAssociative::addrToBlockAddr(unsigned long long addr) {
	int blockAddr = addr / this->blockSize;
	return blockAddr;
}

/****** SetAssociativeSet ******/
SetAssociativeSet::SetAssociativeSet(int mode) {
	this->sa1 = new SetAssociative(32, 16, 2, mode);
	this->sa2 = new SetAssociative(32, 16, 4, mode);
	this->sa3 = new SetAssociative(32, 16, 8, mode);
	this->sa4 = new SetAssociative(32, 16, 16, mode);
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

void SetAssociativeSet::writeRes(ofstream &outfile) {
	outfile << this->sa1->getHit() << "," << this->sa1->getAccess() << "; "
		 << this->sa2->getHit() << "," << this->sa2->getAccess() << "; "
		 << this->sa3->getHit() << "," << this->sa3->getAccess() << "; "
		 << this->sa4->getHit() << "," << this->sa4->getAccess() << ";" << endl;	
}