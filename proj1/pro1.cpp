#include <iostream>
#include <fstream>
#include <string>

#include "AlTaken.h"
#include "AlNonTaken.h"
#include "Bimodal.h"
#include "Gshare.h"


using namespace std;



int main(int argc, char const *argv[])
{
	AlTaken * p1 = new AlTaken();
	AlNonTaken * p2 = new AlNonTaken();

	Bimodal * p3_16 = new Bimodal(1, 16);
	Bimodal * p3_32 = new Bimodal(1, 32);
	Bimodal * p3_128 = new Bimodal(1, 128);
	Bimodal * p3_256 = new Bimodal(1, 256);
	Bimodal * p3_512 = new Bimodal(1, 512);
	Bimodal * p3_1024 = new Bimodal(1, 1024);
	Bimodal * p3_2048 = new Bimodal(1, 2048);

	Bimodal * p4_16 = new Bimodal(2, 16);
	Bimodal * p4_32 = new Bimodal(2, 32);
	Bimodal * p4_128 = new Bimodal(2, 128);
	Bimodal * p4_256 = new Bimodal(2, 256);
	Bimodal * p4_512 = new Bimodal(2, 512);
	Bimodal * p4_1024 = new Bimodal(2, 1024);
	Bimodal * p4_2048 = new Bimodal(2, 2048);

	Gshare * p5_3 = new Gshare(3);
	Gshare * p5_4 = new Gshare(4);
	Gshare * p5_5 = new Gshare(5);
	Gshare * p5_6 = new Gshare(6);
	Gshare * p5_7 = new Gshare(7);
	Gshare * p5_8 = new Gshare(8);
	Gshare * p5_9 = new Gshare(9);
	Gshare * p5_10 = new Gshare(10);
	Gshare * p5_11 = new Gshare(11);

	unsigned long long addr;
	string behavior;
	unsigned long long target;
	

	ifstream infile("p1-resources/examples/test_input.txt");
	// ifstream infile("p1-resources/traces/short_trace1.txt");
	while(infile >> hex >> addr >> behavior >> hex >> target) {
		// p1->processOne(behavior);
		// p2->processOne(behavior);

		// p3_16->processOne(addr, behavior);
		// p3_32->processOne(addr, behavior);
		// p3_128->processOne(addr, behavior);
		// p3_256->processOne(addr, behavior);
		// p3_512->processOne(addr, behavior);
		// p3_1024->processOne(addr, behavior);
		// p3_2048->processOne(addr, behavior);

		// p4_16->processOne(addr, behavior);
		// p4_32->processOne(addr, behavior);
		// p4_128->processOne(addr, behavior);
		// p4_256->processOne(addr, behavior);
		// p4_512->processOne(addr, behavior);
		// p4_1024->processOne(addr, behavior);
		// p4_2048->processOne(addr, behavior);

		p5_3->processOne(addr, behavior);
		p5_4->processOne(addr, behavior);
		p5_5->processOne(addr, behavior);
		p5_6->processOne(addr, behavior);
		p5_7->processOne(addr, behavior);
		p5_8->processOne(addr, behavior);
		p5_9->processOne(addr, behavior);
		p5_10->processOne(addr, behavior);
		p5_11->processOne(addr, behavior);
	}

	// cout << p1->getCorrect() << "," << p1->getNum() << endl;
	// cout << p2->getCorrect() << "," << p2->getNum() << endl;
	// cout << p3_16->getCorrect() << "," << p3_16->getNum() << "; "
	// 	 << p3_32->getCorrect() << "," << p3_32->getNum() << "; "
	// 	 << p3_128->getCorrect() << "," << p3_128->getNum() << "; "
	// 	 << p3_256->getCorrect() << "," << p3_256->getNum() << "; "
	// 	 << p3_512->getCorrect() << "," << p3_512->getNum() << "; "
	// 	 << p3_1024->getCorrect() << "," << p3_1024->getNum() << "; "
	// 	 << p3_2048->getCorrect() << "," << p3_2048->getNum() << "; " << endl;

	// cout << p4_16->getCorrect() << "," << p4_16->getNum() << "; "
	// 	 << p4_32->getCorrect() << "," << p4_32->getNum() << "; "
	// 	 << p4_128->getCorrect() << "," << p4_128->getNum() << "; "
	// 	 << p4_256->getCorrect() << "," << p4_256->getNum() << "; "
	// 	 << p4_512->getCorrect() << "," << p4_512->getNum() << "; "
	// 	 << p4_1024->getCorrect() << "," << p4_1024->getNum() << "; "
	// 	 << p4_2048->getCorrect() << "," << p4_2048->getNum() << "; " << endl;
	
	cout << p5_3->getCorrect() << "," << p5_3->getNum() << "; "
		 << p5_4->getCorrect() << "," << p5_4->getNum() << "; "
		 << p5_5->getCorrect() << "," << p5_5->getNum() << "; "
		 << p5_6->getCorrect() << "," << p5_6->getNum() << "; "
		 << p5_7->getCorrect() << "," << p5_7->getNum() << "; "
		 << p5_8->getCorrect() << "," << p5_8->getNum() << "; "
		 << p5_9->getCorrect() << "," << p5_9->getNum() << "; "
		 << p5_10->getCorrect() << "," << p5_10->getNum() << "; "
		 << p5_11->getCorrect() << "," << p5_11->getNum() << "; " << endl;



	delete p1;
	delete p2;

	delete p3_16;
	delete p3_32;
	delete p3_128;
	delete p3_256;
	delete p3_512;
	delete p3_1024;
	delete p3_2048;

	delete p4_16;
	delete p4_32;
	delete p4_128;
	delete p4_256;
	delete p4_512;
	delete p4_1024;
	delete p4_2048;

	delete p5_3;
	delete p5_4;
	delete p5_5;
	delete p5_6;
	delete p5_7;
	delete p5_8;
	delete p5_9;
	delete p5_10;
	delete p5_11;

	return 0;
}

// int bit = 3;
// int mask = (1 << bit) - 1;
// int history = 0;

// cout << history << endl;

// int newOne = 1;
// history <<= 1;
// history &= mask;
// history += newOne;
// cout << history << endl;
