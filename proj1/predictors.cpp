#include <iostream>
#include <fstream>
#include <string>

#include "AlTaken.h"
#include "AlNonTaken.h"
#include "Bimodal.h"
#include "Gshare.h"
#include "Tournament.h"
#include "BTB.h"

using namespace std;

int main(int argc, char const *argv[])
{
	if (argc != 3) {
		cerr << "Error: the program only takes two parameters." << endl;
		exit(0);
	}

	AlTaken * p1 = new AlTaken();
	AlNonTaken * p2 = new AlNonTaken();
	BimodalSet * p3 = new BimodalSet(1);
	BimodalSet * p4 = new BimodalSet(2);
	GshareSet * p5 = new GshareSet();
	Tournament * p6 = new Tournament(2048);
	BTB * p7 = new BTB();

	unsigned long long addr;
	string behavior;
	unsigned long long target;

	ifstream infile(argv[1]);
	ofstream outfile(argv[2]);
	
	while(infile >> hex >> addr >> behavior >> hex >> target) {
		p1->processOne(behavior);
		p2->processOne(behavior);
		p3->processOne(addr, behavior);
		p4->processOne(addr, behavior);
		p5->processOne(addr, behavior);
		p6->processOne(addr, behavior);
		p7->processOne(addr, behavior, target);
	}

	// Write result
	outfile << p1->getCorrect() << "," << p1->getNum() << ";" << endl;
	outfile << p2->getCorrect() << "," << p2->getNum() << ";" << endl;
	p3->writeRes(outfile);
	p4->writeRes(outfile);
	p5->writeRes(outfile);
	outfile << p6->getCorrect() << "," << p6->getNum() << ";" << endl;
	outfile << p7->getAccess() << "," << p7->getHit() << ";" << endl;

	// Close file
	infile.close();
	outfile.close();
	cout << "All results have been written into file" << endl;

	// Free memory
	delete p1;
	delete p2;
	delete p3;
	delete p4;
	delete p5;
	delete p6;
	delete p7;

	return 0;
}
