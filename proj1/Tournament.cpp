#include "Tournament.h"

Tournament::Tournament() {
	this->pB = new Bimodal(2, 2048);
	this->pG = new Gshare(11);
}

Tournament::~Tournament() {
	delete this->pB;
	delete this->pG;
}


void Tournament::processOne(unsigned long long addr, string behavior) {
	this->num++;
	string predictFromB = this->pB->processOne(addr, behavior);
	string predictFromG = this->pG->processOne(addr, behavior);

	unsigned long long mask = this->tableEntry - 1;
	addr = addr & mask;

	// Whether the two predictions are same
	bool isSame = false;
	if (predictFromG.compare(predictFromB) == 0) isSame = true;

	string predict;
	if (this->selector[addr] < 2) {
		// Prefer Gshare
		predict = predictFromG;
		if (predict.compare(behavior) == 0) {
			// Predict correct
			this->correct++;
			if (!isSame) this->updateSelector(addr, -1);
		} 
		else {
			// Predict wrong
			if (!isSame) this->updateSelector(addr, 1);
		}
	} 
	else {
		// Prefer Bimodal
		predict = predictFromB;
		if (predict.compare(behavior) == 0) {
			// Predict correct
			this->correct++;
			if (!isSame) this->updateSelector(addr, 1);
		}
		else {
			// Predict wrong
			if (!isSame) this->updateSelector(addr, -1);
		}
	}
}

void Tournament::updateSelector(unsigned long long idx, int addNum) {
	int tmp = this->selector[idx] + addNum;
	if (tmp < 0) tmp = 0;
	if (tmp > 3) tmp = 3;
	this->selector[idx] = tmp;
}

int Tournament::getNum() {
	return this->num;
}

int Tournament::getCorrect() {
	return this->correct;
}

