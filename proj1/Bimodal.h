#ifndef _BIMODAL_H_
#define _BIMODAL_H_

#include <string>

using namespace std;


class Bimodal
{
private:
	int num = 0;
	int correct = 0;

	int max; 
	int mid; // [0,mid): Taken; [mid, max): Not Taken

	int tableEntry; // Number of table entry, like 16, 32, 128
	int * table;    // Branch history table, 0: Taken, 1: Not Taken

public:
	Bimodal(int bit, int tableEntry);
	~Bimodal() {delete this->table;};

	string processOne(unsigned long long addr, string behavior);
	void updateTable(unsigned long long idx, int addNum);
	int getNum();
	int getCorrect();
};


#endif

