#include <iostream>
#include <fstream>
#include <string>

#include "AlTaken.h"
#include "AlNonTaken.h"
#include "BimodalWithOne.h"


using namespace std;

void print(AlTaken * p1, AlNonTaken * p2, BimodalWithOne * p3) {
	cout << p1->getCorrect() << "," << p1->getNum() << endl;
	cout << p2->getCorrect() << "," << p2->getNum() << endl;
	cout << p3->getCorrect() << "," << p3->getNum() << endl;
}

int main(int argc, char const *argv[])
{
	AlTaken * p1 = new AlTaken();
	AlNonTaken * p2 = new AlNonTaken();
	BimodalWithOne * p3 = new BimodalWithOne();

	unsigned long long addr;
	string behavior;
	unsigned long long target;
	

	ifstream infile("p1-resources/examples/test_input.txt");
	// ifstream infile("p1-resources/traces/long_trace1.txt");
	while(infile >> hex >> addr >> behavior >> hex >> target) {
		p1->processOne(behavior);
		p2->processOne(behavior);
		p3->processOne(addr, behavior);
	}

	print(p1, p2, p3);


	delete p1;
	delete p2;
	delete p3;

	return 0;
}