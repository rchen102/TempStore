#include <iostream>
#include <fstream>
#include <string>

#include "AlTaken.h"
#include "AlNonTaken.h"
#include "Bimodal.h"
#include "Gshare.h"
#include "Tournament.h"


using namespace std;



int main(int argc, char const *argv[])
{
	AlTaken * p1 = new AlTaken();
	AlNonTaken * p2 = new AlNonTaken();
	BimodalSet * p3 = new BimodalSet(1);
	BimodalSet * p4 = new BimodalSet(2);
	GshareSet * p5 = new GshareSet();
	Tournament * p6 = new Tournament();


	unsigned long long addr;
	string behavior;
	unsigned long long target;

	// ifstream infile("p1-resources/examples/test_input.txt");
	ifstream infile("p1-resources/traces/short_trace1.txt");
	while(infile >> hex >> addr >> behavior >> hex >> target) {
		p1->processOne(behavior);
		p2->processOne(behavior);
		// p3->processOne(addr, behavior);
		// p4->processOne(addr, behavior);
		// p5->processOne(addr, behavior);
		p6->processOne(addr, behavior);
	}

	// Print result
	cout << p1->getCorrect() << "," << p1->getNum() << endl;
	cout << p2->getCorrect() << "," << p2->getNum() << endl;
	// p3->printRes();
	// p4->printRes();
	// p5->printRes();
	cout << p6->getCorrect() << "," << p6->getNum() << endl;

	// Free memory
	delete p1;
	delete p2;
	delete p3;
	delete p4;
	delete p5;
	delete p6;

	return 0;
}
