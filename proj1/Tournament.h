#ifndef _TOURNAMENT_H_
#define _TOURNAMENT_H_

#include <string>
#include "Bimodal.h"
#include "Gshare.h"


using namespace std;

class Tournament
{
private:
	int num = 0;
	int correct = 0;
	int tableEntry = 2048;

	int selector[2048] = {0};
	Bimodal * pB;
	Gshare * pG;

public:
	Tournament();
	~Tournament();
	void processOne(unsigned long long addr, string behavior);
	void updateSelector(unsigned long long idx, int addNum);

	int getNum();
	int getCorrect();
};


#endif

