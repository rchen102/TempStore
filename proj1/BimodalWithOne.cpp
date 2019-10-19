#include "BimodalWithOne.h"
#include <string>

void BimodalWithOne::processOne(unsigned long long addr, string behavior) {
	this->num++;
	this->predictForTable1(addr, behavior);
}

void BimodalWithOne::predictForTable1(unsigned long long addr, string behavior) {
	// Get the index from the lower 4 bits
	unsigned long long mask = 15; 
	addr = addr & mask;

	// Get prediction
	string predict = "T";
	if (this->table1[addr] == 1) predict = "NT"; 

	// Update table
	if (behavior.compare(predict) == 0) this->correct++;
	else this->table1[addr] = !this->table1[addr];
}

int BimodalWithOne::getNum() {
	return this->num;
}
int BimodalWithOne::getCorrect() {
	return this->correct;
}

