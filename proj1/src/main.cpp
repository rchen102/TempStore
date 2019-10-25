#include <iostream>
#include <fstream>
#include <string>

#include "../include/Predictors.h"

using namespace std;

int main(int argc, char const *argv[])
{
	if (argc != 3) {
		cerr << "Error: the program only takes two parameters." << endl;
		exit(0);
	}

	// File process
	unsigned long long addr;
	string behavior;
	unsigned long long target;

	ifstream infile(argv[1]);
	ofstream outfile(argv[2]);

	if (!infile) {
		cerr << "\nError Message:"<< endl;
		cerr << "Can't find file '" << argv[1] << "'" << endl;
		cerr << "Please check if the filename is correct or file has been placed in correct directory" << endl;
		exit(0);
 	}

 	// Do prediction
 	Predictors * p = new Predictors();
	while(infile >> hex >> addr >> behavior >> hex >> target) {
		p->processOne(addr, behavior, target);
	}
	p->writeRes(outfile);
	p->printRes();

	// Close file and free memory
	infile.close();
	outfile.close();
	delete p;

	cout << "\nAll results have been written into file '" << argv[2] << "'" << endl;
	return 0;
}
