#include "AlTaken.h"
#include <string>

void AlTaken::processOne(string behavior) {
	this->num++;
	if (behavior.compare("T") == 0) this->correct++;
}

int AlTaken::getNum() {
	return this->num;
}
int AlTaken::getCorrect() {
	return this->correct;
}

