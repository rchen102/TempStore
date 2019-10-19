#ifndef _ALNONTAKEN_H_
#define _ALNONTAKEN_H_

#include <string>

using namespace std;

class AlNonTaken
{
private:
	int num = 0;
	int correct = 0;

public:
	void processOne(string behavior);
	int getNum();
	int getCorrect();
};


#endif

