#include "../include/Bimodal.h"
#include <iostream>

/****** Bimodal******/
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
	// Do prediction and update
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


/****** BimodalSet ******/
BimodalSet::BimodalSet(int bit) {
	this->p_16 = new Bimodal(bit, 16);
	this->p_32 = new Bimodal(bit, 32);
	this->p_128 = new Bimodal(bit, 128);
	this->p_256 = new Bimodal(bit, 256);
	this->p_512 = new Bimodal(bit, 512);
	this->p_1024 = new Bimodal(bit, 1024);
	this->p_2048 = new Bimodal(bit, 2048);
}

BimodalSet::~BimodalSet() {
	delete this->p_16;
	delete this->p_32;
	delete this->p_128;
	delete this->p_256;
	delete this->p_512;
	delete this->p_1024;
	delete this->p_2048;
}

void BimodalSet::processOne(unsigned long long addr, string behavior) {
	this->p_16->processOne(addr, behavior);
	this->p_32->processOne(addr, behavior);
	this->p_128->processOne(addr, behavior);
	this->p_256->processOne(addr, behavior);
	this->p_512->processOne(addr, behavior);
	this->p_1024->processOne(addr, behavior);
	this->p_2048->processOne(addr, behavior);
}

void BimodalSet::writeRes(ofstream &outfile) {
	outfile << this->p_16->getCorrect() << "," << this->p_16->getNum() << "; "
		 << this->p_32->getCorrect() << "," << this->p_32->getNum() << "; "
		 << this->p_128->getCorrect() << "," << this->p_128->getNum() << "; "
		 << this->p_256->getCorrect() << "," << this->p_256->getNum() << "; "
		 << this->p_512->getCorrect() << "," << this->p_512->getNum() << "; "
		 << this->p_1024->getCorrect() << "," << this->p_1024->getNum() << "; "
		 << this->p_2048->getCorrect() << "," << this->p_2048->getNum() << ";" << std::endl;
}

