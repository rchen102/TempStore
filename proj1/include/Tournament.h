#ifndef _TOURNAMENT_H_
#define _TOURNAMENT_H_

#include <string>
#include "Bimodal.h"
#include "Gshare.h"

using std::string;

class Tournament
{
private:
	int num = 0;
	int correct = 0;
	
	int tableEntry;
	int * selector;
	
	Bimodal * pB;
	Gshare * pG;

public:
	Tournament(int tableEntry);
	~Tournament();
	void processOne(unsigned long long addr, string behavior);
	void updateSelector(unsigned long long idx, int addNum);

	int getNum();
	int getCorrect();
};

#endif

