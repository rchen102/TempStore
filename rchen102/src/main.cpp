#include <iostream>
#include <fstream>
#include <string>

#include "../include/CacheSimulator.h"

using namespace std;

int main(int argc, char const *argv[])
{
	if (argc != 3) {
		cerr << "Error: the program only takes two parameters." << endl;
		exit(0);
	}

	// File process
	string behavior;
	unsigned long long addr;

	ifstream infile(argv[1]);
	ofstream outfile(argv[2]);

	if (!infile) {
		cerr << "\nError Message:"<< endl;
		cerr << "Can't find file '" << argv[1] << "'" << endl;
		cerr << "Please check whether filename is correct or file under correct directory" << endl;
		exit(0);
 	}

 	// Do simulation
 	CacheSimulator * cache_sim = new CacheSimulator();
	while(infile >> behavior >> hex >> addr) {
		cache_sim->processOne(behavior, addr);
	}
	cache_sim->printRes();
	cache_sim->writeRes(outfile);

	// Close file and free memory
	infile.close();
	outfile.close();
	delete cache_sim;

	cout << "-----All results have been written into file '" << argv[2] << "'------" << endl;	
	return 0;
}
