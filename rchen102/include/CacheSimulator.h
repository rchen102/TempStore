#ifndef _CACHE_SIMULATOR_H_
#define _CACHE_SIMULATOR_H_

#include <string>
// #include <fstream>

#include "DirectMappedCache.h"

using std::string;

class CacheSimulator
{
private:
	DirectMappedCacheSet * dmc;

public:
	CacheSimulator();
	~CacheSimulator();
	void processOne(string behavior, unsigned long long addr);

	void printOne(int hit, int access);
	void printRes();
	// void writeRes(ofstream &outfile);
	
};

#endif