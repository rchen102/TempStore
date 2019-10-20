#include "BTB.h"

BTB::BTB() {
	this->pB = new Bimodal(1, 512);
}

BTB::~BTB() {
	delete this->pB;
}


void BTB::processOne(unsigned long long addr, string behavior, unsigned long long target) {
	string predictFromB = this->pB->processOne(addr, behavior);

	unsigned long long mask = 128 - 1;
	unsigned long long idx = addr & mask;
	if (predictFromB.compare("T") == 0) {
		this->access++;
		if (this->bufferIsInitialized[idx] == 0) {
			// The buffer has never been used
			this->bufferIsInitialized[idx] = 1;
			this->pc[idx] = addr;
			this->targetBuffer[idx] = target;
		} else {
			if (this->pc[idx] == addr) this->hit++;
			else {
				this->pc[idx] = addr;
				this->targetBuffer[idx] = target;
			}
		}
	}
}

int BTB::getAccess() {
	return this->access;
}

int BTB::getHit() {
	return this->hit;
}

