#ifndef _LRU_H_
#define _LRU_H_

#include <map>

using std::map;

class Node 
{
public:
	Node * pre;
	Node * next;
	int key;

	Node(int key);
};

class LRU
{
public:
	map<int, Node*> keyNodemap;
	Node * head;    // dummy node exist
	Node * tail;    // head: oldest, tail: youngest

	int capacity;
	int num;

public:
	LRU(int capacity);
	~LRU();
	
	int access(int key);  // return 1, if hit; else -1
	void updateToTail(Node * node);
	void insert(int key);
	void evictOne();
	void show();	
};

#endif