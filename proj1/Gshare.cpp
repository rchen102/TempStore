#include "Gshare.h"
#include <string>

#include <iostream>

Gshare::Gshare(int bit) {
	this->p = new Bimodal(2, 2048);
	this->maskForHis = (1 << bit) - 1;
}

string Gshare::processOne(unsigned long long addr, string behavior) {
	unsigned long long idx = this->computeIndex(addr);
	string predict = this->p->predictAndUpdateTableAt(idx, behavior);
	this->updateHistory(behavior);
	return predict;
}

unsigned long long Gshare::computeIndex(unsigned long long addr) {
	unsigned long long mask = this->tableEntry - 1;
	addr &= mask;

	// Do xor
	unsigned long long temp = addr & this->maskForHis;
	temp ^= this->history;
	temp &= this->maskForHis;

	// Combine
	addr &= (~this->maskForHis);
	addr += temp;
	return addr;
}

void Gshare::updateHistory(string behavior) {
	this->history <<= 1;
	this->history &= this->maskForHis;
	if (behavior.compare("T") == 0) this->history += 1;
}


int Gshare::getNum() {
	return this->p->getNum();
}
int Gshare::getCorrect() {
	return this->p->getCorrect();
}

