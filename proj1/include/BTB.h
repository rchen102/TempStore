#ifndef _BTB_H_
#define _BTB_H_

#include <string>
#include "Bimodal.h"
#include "Gshare.h"

using namespace std;

class BTB
{
private:
	int access = 0;
	int hit = 0;

	int bufferIsInitialized[128] = {0}; // In case, address or target is 0
	unsigned long long pc[128] = {0};
	unsigned long long targetBuffer[128] = {0};
	Bimodal * pB;

public:
	BTB();
	~BTB();

	void processOne(unsigned long long addr, string behavior, unsigned long long target);
	int getAccess();
	int getHit();
};


#endif

