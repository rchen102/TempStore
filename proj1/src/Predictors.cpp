#include "../include/Predictors.h"
#include <iostream>

using std::cout;
using std::endl;

Predictors::Predictors() {
	this->p1 = new AlTaken();
	this->p2 = new AlNonTaken();
	this->p3 = new BimodalSet(1);
	this->p4 = new BimodalSet(2);
	this->p5 = new GshareSet();
	this->p6 = new Tournament(2048);
	this->p7 = new BTB();
}

Predictors::~Predictors() {
	delete this->p1;
	delete this->p2;
	delete this->p3;
	delete this->p4;
	delete this->p5;
	delete this->p6;
	delete this->p7;
}

void Predictors::processOne(unsigned long long addr, string behavior, unsigned long long target) {
	this->p1->processOne(behavior);
	this->p2->processOne(behavior);
	this->p3->processOne(addr, behavior);
	this->p4->processOne(addr, behavior);
	this->p5->processOne(addr, behavior);
	this->p6->processOne(addr, behavior);
	this->p7->processOne(addr, behavior, target);
}

void Predictors::writeRes(ofstream &outfile) {
	outfile << this->p1->getCorrect() << "," << this->p1->getNum() << ";" << endl;
	outfile << this->p2->getCorrect() << "," << this->p2->getNum() << ";" << endl;
	this->p3->writeRes(outfile);
	this->p4->writeRes(outfile);
	this->p5->writeRes(outfile);
	outfile << this->p6->getCorrect() << "," << this->p6->getNum() << ";" << endl;
	outfile << this->p7->getAccess() << "," << this->p7->getHit() << ";" << endl;
}

void Predictors::printRes() {
	cout << "\nPrint results: " << endl;
	cout << this->p1->getCorrect() << "," << this->p1->getNum() << ";" << endl;
	cout << this->p2->getCorrect() << "," << this->p2->getNum() << ";" << endl;
	this->p3->printRes();
	this->p4->printRes();
	this->p5->printRes();
	cout << this->p6->getCorrect() << "," << this->p6->getNum() << ";" << endl;
	cout << this->p7->getAccess() << "," << this->p7->getHit() << ";" << endl;
}