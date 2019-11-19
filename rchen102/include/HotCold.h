#ifndef _HotCold_H_
#define _HotCold_H_

class HotCold
{
public:
	int capacity;

	int * cache;   // the tag
	int * tree;    // hot code tree

public:
	HotCold(int capacity);
	~HotCold();

	void updateTreeWithHit(int blockIdx);
	void updateTreeWithMiss(int blockAddr);
	int access(int blockAddr);   // 1 for hit, -1 for miss
};

#endif