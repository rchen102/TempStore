#ifndef _BIMODAL_WITH_ONE_H_
#define _BIMODAL_WITH_ONE_H_

#include <string>

using namespace std;

class BimodalWithOne
{
private:
	int num = 0;
	int correct = 0;

	int table1[16] = {0}; // O: Taken; 1: Not Taken

public:
	void processOne(unsigned long long addr, string behavior);
	void predictForTable1(unsigned long long addr, string behavior);
	int getNum();
	int getCorrect();
};


#endif

