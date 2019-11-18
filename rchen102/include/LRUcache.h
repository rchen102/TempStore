#ifndef _LRU_CACHE_H_
#define _LRU_CACHE_H_

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

class LRUcache
{
private:
	map<int, Node*> keyNodemap;
	Node * head;    // dummy node exist
	Node * tail;    // head: oldest, tail: youngest

	int capacity;
	int num;

public:
	LRUcache(int capacity);
	~LRUcache();
	
	void access(int key);
	void updateToTail(Node * node);
	void insert(int key);
	void evictOne();
	void show();	
};

#endif