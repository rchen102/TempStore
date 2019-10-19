#ifndef _GSHARE_H_
#define _GSHARE_H_

#include <string>
#include "Bimodal.h"

using namespace std;


class Gshare
{
private:
	Bimodal * p;
	int tableEntry = 2048;

	int history = 0;
	int maskForHis; // mask for history bit

public:
	Gshare(int bit);
	~Gshare() {delete this->p;};

	string processOne(unsigned long long addr, string behavior);
	unsigned long long computeIndex(unsigned long long addr);
	void updateHistory(string predict);

	int getNum();
	int getCorrect();
};


#endif

