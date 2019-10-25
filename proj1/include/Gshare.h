#ifndef _GSHARE_H_
#define _GSHARE_H_

#include <string>
#include <fstream>
#include "Bimodal.h"

using std::string;
using std::ofstream;

class Gshare
{
private:
	Bimodal * p;
	int tableEntry;

	int history = 0;
	int maskForHis; // mask for history bit

public:
	Gshare(int bit, int tableEntry);
	~Gshare() {delete this->p;};

	string processOne(unsigned long long addr, string behavior);
	unsigned long long computeIndex(unsigned long long addr);
	void updateHistory(string predict);
	int getNum();
	int getCorrect();
};

class GshareSet {
private:
	Gshare * p5_3;
	Gshare * p5_4;
	Gshare * p5_5;
	Gshare * p5_6;
	Gshare * p5_7;
	Gshare * p5_8;
	Gshare * p5_9;
	Gshare * p5_10;
	Gshare * p5_11;

public:
	GshareSet();
	~GshareSet();

	void processOne(unsigned long long addr, string behavior);
	void writeRes(ofstream &outfile);
	void printRes();
};

#endif

