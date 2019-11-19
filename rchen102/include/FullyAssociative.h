#ifndef _FULLY_ASSOCIATIVE_H_
#define _FULLY_ASSOCIATIVE_H_

#include <string>
// #include <fstream>

#include "LRU.h"

using std::string;

class FullyAssociative
{
private:
	int blockSize;   // bytes
	int cacheSize;   // bytes
	
	int blockNum;    // total block #

	int hit;
	int access;	

	int mode;
	LRU * LRUcache;

public:
	FullyAssociative(int blockSize, int cacheSize, int mode);  // mode 0 for LRU, mode 1 for hot/cold
	~FullyAssociative();

	void processOne(string behavior, unsigned long long addr);
	int addrToBlockAddr(unsigned long long addr);

	int getHit() {return this->hit;};
	int getAccess() {return this->access;};
	
};

#endif