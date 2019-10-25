#ifndef _ALNONTAKEN_H_
#define _ALNONTAKEN_H_

#include <string>

using std::string;

class AlNonTaken
{
private:
	int num = 0;
	int correct = 0;

public:
	string processOne(std::string behavior);
	int getNum();
	int getCorrect();
};

#endif