#ifndef _DIRECT_MAPPED_CACHE_H_
#define _DIRECT_MAPPED_CACHE_H_

#include <string>
// #include <fstream>

using std::string;

class DirectMappedCache
{
private:
	int lineSize;   // bytes
	int cacheSize;  // bytes
	int num;        // line number

	int hit;
	int access;

	int * tag;
	int * valid;

public:
	DirectMappedCache(int lineSize, int cacheSize);   // unit: (bytes, kb)
	~DirectMappedCache();
	
	void processOne(string behavior, unsigned long long addr);
	int addrToLineAddr(unsigned long long addr);

	int getHit() {return this->hit;};
	int getAccess() {return this->access;};
};


class DirectMappedCacheSet {
private:
	DirectMappedCache * dmc1;
	DirectMappedCache * dmc2;
	DirectMappedCache * dmc3;
	DirectMappedCache * dmc4;

public:
	DirectMappedCacheSet();
	~DirectMappedCacheSet();

	void processOne(string behavior, unsigned long long addr);

	void printRes();
};

#endif