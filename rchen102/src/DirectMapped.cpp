#include "../include/DirectMapped.h"
#include <iostream>

using std::cout;
using std::endl;

/****** DirectMapped ******/
DirectMapped::DirectMapped(int blockSize, int cacheSize) {
	this->blockSize = blockSize;
	this->cacheSize = 1024 * cacheSize;
	this->blockNum = this->cacheSize / this->blockSize;

	this->hit = 0;
	this->access = 0;

	this->tag = new int[this->blockNum]();
	this->valid = new int[this->blockNum]();     // initialize to 0, 0->invalid, 1->valid
}

DirectMapped::~DirectMapped() {
	delete[] this->tag;
	delete[] this->valid;
}

void DirectMapped::processOne(string behavior, unsigned long long addr) {
	this->access++;
	int blockAddr = this->addrToBlockAddr(addr);    // transfer address to block address
	int blockIdx = blockAddr % this->blockNum;      // get block index(block number) by block address

	if (this->valid[blockIdx] == 0) {
		this->tag[blockIdx] = blockAddr;
		this->valid[blockIdx] = 1;
	} 
	else if (this->valid[blockIdx] == 1) {
		if (this->tag[blockIdx] == blockAddr) this->hit++;
		else {
			this->tag[blockIdx] = blockAddr;
		}
	}
}

int DirectMapped::addrToBlockAddr(unsigned long long addr) {
	int blockAddr = addr / this->blockSize;
	return blockAddr;
}


/****** DirectMappedSet ******/
DirectMappedSet::DirectMappedSet() {
	this->dmc1 = new DirectMapped(32, 1);
	this->dmc2 = new DirectMapped(32, 4);
	this->dmc3 = new DirectMapped(32, 16);
	this->dmc4 = new DirectMapped(32, 32);
}

DirectMappedSet::~DirectMappedSet() {
	delete this->dmc1;
	delete this->dmc2;
	delete this->dmc3;
	delete this->dmc4;
}

void DirectMappedSet::processOne(string behavior, unsigned long long addr) {
	this->dmc1->processOne(behavior, addr);
	this->dmc2->processOne(behavior, addr);
	this->dmc3->processOne(behavior, addr);
	this->dmc4->processOne(behavior, addr);
}

void DirectMappedSet::printRes() {
	cout << this->dmc1->getHit() << "," << this->dmc1->getAccess() << "; "
		 << this->dmc2->getHit() << "," << this->dmc2->getAccess() << "; "
		 << this->dmc3->getHit() << "," << this->dmc3->getAccess() << "; "
		 << this->dmc4->getHit() << "," << this->dmc4->getAccess() << ";" << endl;
}

void DirectMappedSet::writeRes(ofstream &outfile) {
	outfile << this->dmc1->getHit() << "," << this->dmc1->getAccess() << "; "
		 << this->dmc2->getHit() << "," << this->dmc2->getAccess() << "; "
		 << this->dmc3->getHit() << "," << this->dmc3->getAccess() << "; "
		 << this->dmc4->getHit() << "," << this->dmc4->getAccess() << ";" << endl;	
}