#include "../include/CacheSimulator.h"
#include <iostream>

using std::cout;
using std::endl;

CacheSimulator::CacheSimulator() {
	this->dmc = new DirectMappedSet();
	this->sa = new SetAssociativeSet(0);     // mode 0, default Set-Associative cache set
	this->fa1 = new FullyAssociative(32, 16, 0);   // block size 32bytes, cache size 16kb, mode 0 (LRU)
	this->fa2 = new FullyAssociative(32, 16, 1);   // block size 32bytes, cache size 16kb, mode 1 (HotCold)
	this->sa1 = new SetAssociativeSet(1);    // mode 1 (No Allocation on a Write Miss)
	this->sa2 = new SetAssociativeSet(2);    // mode 2 (Next-line Prefetching)
	this->sa3 = new SetAssociativeSet(3);    // mode 3 (Prefetch on a Miss)
}

CacheSimulator::~CacheSimulator() {
	delete this->dmc;
	delete this->sa;
	delete this->fa1;
	delete this->fa2;
	delete this->sa1;
	delete this->sa2;
	delete this->sa3;
}

void CacheSimulator::processOne(string behavior, unsigned long long addr) {
	this->dmc->processOne(behavior, addr);
	this->sa->processOne(behavior, addr);
	this->fa1->processOne(behavior, addr);
	this->fa2->processOne(behavior, addr);
	this->sa1->processOne(behavior, addr);
	this->sa2->processOne(behavior, addr);
	this->sa3->processOne(behavior, addr);
}

void CacheSimulator::printOne(int hit, int access) {
	cout << hit << "," << access << ";" << endl;
}

void CacheSimulator::printRes() {
	cout << "\nPrint results: " << endl;
	this->dmc->printRes();
	this->sa->printRes();
	this->printOne(this->fa1->getHit(), this->fa1->getAccess());
	this->printOne(this->fa2->getHit(), this->fa2->getAccess());
	this->sa1->printRes();
	this->sa2->printRes();
	this->sa3->printRes();
}

void CacheSimulator::writeRes(ofstream &outfile) {
	this->dmc->writeRes(outfile);
	this->sa->writeRes(outfile);
	outfile << this->fa1->getHit() << "," << this->fa1->getAccess() << ";" << endl;
	outfile << this->fa2->getHit() << "," << this->fa2->getAccess() << ";" << endl;
	this->sa1->writeRes(outfile);
	this->sa2->writeRes(outfile);
	this->sa3->writeRes(outfile);
}

