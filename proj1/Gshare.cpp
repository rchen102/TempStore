#include "Gshare.h"
#include <iostream>

/****** Gshare ******/

Gshare::Gshare(int bit, int tableEntry) {
	this->tableEntry = tableEntry;
	this->p = new Bimodal(2, this->tableEntry);
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
	addr ^= this->history;
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

/****** GshareSet ******/

GshareSet::GshareSet() {
	this->p5_3 = new Gshare(3, 2048);
	this->p5_4 = new Gshare(4, 2048);
	this->p5_5 = new Gshare(5, 2048);
	this->p5_6 = new Gshare(6, 2048);
	this->p5_7 = new Gshare(7, 2048);
	this->p5_8 = new Gshare(8, 2048);
	this->p5_9 = new Gshare(9, 2048);
	this->p5_10 = new Gshare(10, 2048);
	this->p5_11 = new Gshare(11, 2048);
}

GshareSet::~GshareSet() {
	delete this->p5_3;
	delete this->p5_4;
	delete this->p5_5;
	delete this->p5_6;
	delete this->p5_7;
	delete this->p5_8;
	delete this->p5_9;
	delete this->p5_10;
	delete this->p5_11;
}

void GshareSet::processOne(unsigned long long addr, string behavior) {
	this->p5_3->processOne(addr, behavior);
	this->p5_4->processOne(addr, behavior);
	this->p5_5->processOne(addr, behavior);
	this->p5_6->processOne(addr, behavior);
	this->p5_7->processOne(addr, behavior);
	this->p5_8->processOne(addr, behavior);
	this->p5_9->processOne(addr, behavior);
	this->p5_10->processOne(addr, behavior);
	this->p5_11->processOne(addr, behavior);
}

void GshareSet::writeRes(ofstream &outfile) {
	outfile << this->p5_3->getCorrect() << "," << this->p5_3->getNum() << "; "
	 << this->p5_4->getCorrect() << "," << this->p5_4->getNum() << "; "
	 << this->p5_5->getCorrect() << "," << this->p5_5->getNum() << "; "
	 << this->p5_6->getCorrect() << "," << this->p5_6->getNum() << "; "
	 << this->p5_7->getCorrect() << "," << this->p5_7->getNum() << "; "
	 << this->p5_8->getCorrect() << "," << this->p5_8->getNum() << "; "
	 << this->p5_9->getCorrect() << "," << this->p5_9->getNum() << "; "
	 << this->p5_10->getCorrect() << "," << this->p5_10->getNum() << "; "
	 << this->p5_11->getCorrect() << "," << this->p5_11->getNum() << ";" << std::endl;
}

