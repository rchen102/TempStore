#ifndef _PREDICTORS_H_
#define _PREDICTORS_H_

#include <string>
#include <fstream>
#include "AlTaken.h"
#include "AlNonTaken.h"
#include "Bimodal.h"
#include "Gshare.h"
#include "Tournament.h"
#include "BTB.h"

using std::string;

class Predictors
{
private:
	AlTaken * p1;
	AlNonTaken * p2;
	BimodalSet * p3;
	BimodalSet * p4;
	GshareSet * p5;
	Tournament * p6;
	BTB * p7;

public:
	Predictors();
	~Predictors();
	void processOne(unsigned long long addr, string behavior, unsigned long long target);
	void writeRes(ofstream &outfile);
	void printRes();
};

#endif