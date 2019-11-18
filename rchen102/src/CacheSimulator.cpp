#include "../include/CacheSimulator.h"
#include <iostream>

using std::cout;
using std::endl;

CacheSimulator::CacheSimulator() {
	this->dmc = new DirectMappedCacheSet();
}

CacheSimulator::~CacheSimulator() {
	delete this->dmc;
}

void CacheSimulator::processOne(string behavior, unsigned long long addr) {
	this->dmc->processOne(behavior, addr);
}

void CacheSimulator::printOne(int hit, int access) {
	cout << hit << "," << access << ";" << endl;
}

void CacheSimulator::printRes() {
	cout << "\nPrint results: " << endl;
	this->dmc->printRes();
}

// void CacheSimulator::writeRes(ofstream &outfile) {
// 	outfile << this->p1->getCorrect() << "," << this->p1->getNum() << ";" << endl;
// 	outfile << this->p2->getCorrect() << "," << this->p2->getNum() << ";" << endl;
// 	this->p3->writeRes(outfile);
// 	this->p4->writeRes(outfile);
// 	this->p5->writeRes(outfile);
// 	outfile << this->p6->getCorrect() << "," << this->p6->getNum() << ";" << endl;
// 	outfile << this->p7->getAccess() << "," << this->p7->getHit() << ";" << endl;
// }

