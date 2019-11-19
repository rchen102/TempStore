#ifndef _SET_ASSOCIATIVE_H_
#define _SET_ASSOCIATIVE_H_

#include <string>
#include "LRU.h"
// #include <fstream>

using std::string;

class SetAssociative
{
private:
	int blockSize;   // bytes
	int cacheSize;  // bytes

	int blockNum;   // total block #
	int setNum;     // total set #

	int hit;
	int access;

	LRU ** cache;


public:
	SetAssociative(int blockSize, int cacheSize, int associativity);   // unit: (bytes, kb, 1)
	~SetAssociative();
	
	void processOne(string behavior, unsigned long long addr);
	int addrToBlockIndex(unsigned long long addr);

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
	SetAssociativeSet();
	~SetAssociativeSet();

	void processOne(string behavior, unsigned long long addr);

	void printRes();
};

#endif