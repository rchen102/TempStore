#ifndef _CACHE_SIMULATOR_H_
#define _CACHE_SIMULATOR_H_

#include <string>
// #include <fstream>

#include "DirectMapped.h"
#include "SetAssociative.h"
#include "FullyAssociative.h"

using std::string;

class CacheSimulator
{
private:
	DirectMappedSet * dmc;
	SetAssociativeSet * sa;
	FullyAssociative * fa1;   // LRU
	FullyAssociative * fa2;   // HotCold
	SetAssociativeSet * sa1;

public:
	CacheSimulator();
	~CacheSimulator();
	void processOne(string behavior, unsigned long long addr);

	void printOne(int hit, int access);
	void printRes();
	// void writeRes(ofstream &outfile);
	
};

#endif