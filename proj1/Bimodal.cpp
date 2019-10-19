#include "Bimodal.h"
#include <string>

Bimodal::Bimodal(int bit, int tableEntry) {
	this->max = (1 << bit) - 1;
	this->mid = (1 << (bit - 1));

	this->tableEntry = tableEntry;
	this->table = new int[tableEntry]();
}

string Bimodal::processOne(unsigned long long addr, string behavior) {
	// Calculate index
	unsigned long long mask = this->tableEntry - 1;
	addr = addr & mask;

	return this->predictAndUpdateTableAt(addr, behavior);
}

string Bimodal::predictAndUpdateTableAt(unsigned long long idx, string behavior) {
	this->num++;
	// Do prediction
	string predict = "NT";
	if(this->table[idx] < this->mid) predict = "T";

	// Do update
	if (behavior.compare(predict) == 0) {
		// Prediction is correct
		this->correct++;
		if (predict.compare("T") == 0) this->updateTable(idx, -1);
		else this->updateTable(idx, 1);
	} 
	else {
		// Prediction is wrong
		if (predict.compare("T") == 0) this->updateTable(idx, 1);
		else this->updateTable(idx, -1);
	}
	return predict;
}

void Bimodal::updateTable(unsigned long long idx, int addNum) {
	int tmp = this->table[idx] + addNum;
	if (tmp < 0) tmp = 0;
	if (tmp > this->max) tmp = this->max;
	this->table[idx] = tmp;
}

int Bimodal::getNum() {
	return this->num;
}
int Bimodal::getCorrect() {
	return this->correct;
}

