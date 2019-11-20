#ifndef _DIRECT_MAPPED_H_
#define _DIRECT_MAPPED_H_

#include <string>
#include <fstream>

using std::string;
using std::ofstream;

class DirectMapped
{
private:
	int blockSize;   // bytes
	int cacheSize;   // bytes
	int blockNum;    // total block #

	int hit;
	int access;

	int * tag;
	int * valid;

public:
	DirectMapped(int blockSize, int cacheSize);   // unit: (bytes, kb)
	~DirectMapped();
	
	void processOne(string behavior, unsigned long long addr);
	int addrToBlockAddr(unsigned long long addr);

	int getHit() {return this->hit;};
	int getAccess() {return this->access;};
};


class DirectMappedSet {
private:
	DirectMapped * dmc1;
	DirectMapped * dmc2;
	DirectMapped * dmc3;
	DirectMapped * dmc4;

public:
	DirectMappedSet();
	~DirectMappedSet();

	void processOne(string behavior, unsigned long long addr);

	void printRes();
	void writeRes(ofstream &outfile);
};

#endif