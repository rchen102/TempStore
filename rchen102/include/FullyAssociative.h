#ifndef _FULLY_ASSOCIATIVE_H_
#define _FULLY_ASSOCIATIVE_H_

#include <string>
// #include <fstream>

#include "LRU.h"
#include "HotCold.h"

using std::string;

class FullyAssociative
{
private:
	int blockSize;   // bytes
	int cacheSize;   // bytes
	
	int blockNum;    // total block #

	int hit;
	int access;	

	int mode;        // 0 for LRU, 1 for HotCold
	LRU * LRUcache;
	HotCold * HotColdcache;

public:
	FullyAssociative(int blockSize, int cacheSize, int mode);  // 0 for LRU, 1 for HotCold
	~FullyAssociative();

	void processOne(string behavior, unsigned long long addr);
	int addrToBlockAddr(unsigned long long addr);

	int getHit() {return this->hit;};
	int getAccess() {return this->access;};
	
};

#endif