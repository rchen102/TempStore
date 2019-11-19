#ifndef _SET_ASSOCIATIVE_H_
#define _SET_ASSOCIATIVE_H_

#include <string>
// #include <fstream>

#include "LRU.h"

using std::string;

class SetAssociative
{
private:
	int blockSize;   // bytes
	int cacheSize;   // bytes

	int blockNum;    // total block #
	int setNum;      // total set #

	int hit;
	int access;

	int mode;        // 0: default, 1: with no Allocation on a Write Miss, 2: prefetch

	LRU ** cache;


public:
	SetAssociative(int blockSize, int cacheSize, int associativity, int mode);   // unit: (bytes, kb, 1)
	~SetAssociative();
	
	void processOne(string behavior, unsigned long long addr);
	int addrToBlockAddr(unsigned long long addr);

	int getHit() {return this->hit;};
	int getAccess() {return this->access;};
};


class SetAssociativeSet {
private:
	SetAssociative * sa1;
	SetAssociative * sa2;
	SetAssociative * sa3;
	SetAssociative * sa4;

public:
	SetAssociativeSet(int mode);
	~SetAssociativeSet();

	void processOne(string behavior, unsigned long long addr);

	void printRes();
};

#endif