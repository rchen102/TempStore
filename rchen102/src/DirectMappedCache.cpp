#include "../include/DirectMappedCache.h"
#include <iostream>

using std::cout;
using std::endl;

/****** DirectMappedCache ******/
DirectMappedCache::DirectMappedCache(int lineSize, int cacheSize) {
	this->lineSize = lineSize;
	this->cacheSize = 1024 * cacheSize;
	this->num = this->cacheSize / this->lineSize;

	this->hit = 0;
	this->access = 0;

	this->tag = new int[this->num]();
	this->valid = new int[this->num]();     // initialize to 0, 0->invalid, 1->valid
}


DirectMappedCache::~DirectMappedCache() {
	delete[] this->tag;
	delete[] this->valid;
}

void DirectMappedCache::processOne(string behavior, unsigned long long addr) {
	this->access++;
	int lineAddress = this->addrToLineAddr(addr);
	int lineNum =lineAddress % this->num;

	if (this->valid[lineNum] == 0) {
		this->tag[lineNum] = lineAddress;
		this->valid[lineNum] = 1;
	} 
	else if (this->valid[lineNum] == 1) {
		if (this->tag[lineNum] == lineAddress) this->hit++;
		else {
			this->tag[lineNum] = lineAddress;
		}
	}
}

int DirectMappedCache::addrToLineAddr(unsigned long long addr) {
	int lineAddress = addr / this->lineSize;
	return lineAddress;
}


/****** DirectMappedCacheSet ******/
DirectMappedCacheSet::DirectMappedCacheSet() {
	this->dmc1 = new DirectMappedCache(32, 1);
	this->dmc2 = new DirectMappedCache(32, 4);
	this->dmc3 = new DirectMappedCache(32, 16);
	this->dmc4 = new DirectMappedCache(32, 32);
}

DirectMappedCacheSet::~DirectMappedCacheSet() {
	delete this->dmc1;
	delete this->dmc2;
	delete this->dmc3;
	delete this->dmc4;
}

void DirectMappedCacheSet::processOne(string behavior, unsigned long long addr) {
	this->dmc1->processOne(behavior, addr);
	this->dmc2->processOne(behavior, addr);
	this->dmc3->processOne(behavior, addr);
	this->dmc4->processOne(behavior, addr);
}

void DirectMappedCacheSet::printRes() {
	cout << this->dmc1->getHit() << "," << this->dmc1->getAccess() << "; "
		 << this->dmc2->getHit() << "," << this->dmc2->getAccess() << "; "
		 << this->dmc3->getHit() << "," << this->dmc3->getAccess() << "; "
		 << this->dmc4->getHit() << "," << this->dmc4->getAccess() << ";" << endl;
}