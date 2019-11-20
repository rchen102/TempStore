#ifndef _HotCold_H_
#define _HotCold_H_

class HotCold
{
public:
	int capacity;

	int * cache;   // store the tag (block address)
	int * tree;    // hot/cold tree

public:
	HotCold(int capacity);
	~HotCold();

	int access(int blockAddr);               // return 1 for hit, -1 for miss
	void updateTreeWithHit(int blockIdx);
	void updateTreeWithMiss(int blockAddr);
	void updateHotColdBit(int treeIdx);
	
};

#endif