#include "AlTaken.h"

string AlTaken::processOne(string behavior) {
	this->num++;
	if (behavior.compare("T") == 0) this->correct++;
	return "T";
}

int AlTaken::getNum() {
	return this->num;
}

int AlTaken::getCorrect() {
	return this->correct;
}