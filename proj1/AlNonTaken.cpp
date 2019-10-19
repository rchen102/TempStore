#include "AlNonTaken.h"

void AlNonTaken::processOne(string behavior) {
	this->num++;
	if (behavior.compare("NT") == 0) this->correct++;
}

int AlNonTaken::getNum() {
	return this->num;
}

int AlNonTaken::getCorrect() {
	return this->correct;
}

