#ifndef _ALTAKEN_H_
#define _ALTAKEN_H_

#include <string>

using namespace std;

class AlTaken
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

