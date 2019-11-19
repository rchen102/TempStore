#include "../include/LRU.h"

#include <iostream>

using std::map;
using std::cout;
using std::endl;


/*******Node*******/
Node::Node(int key) {
	this->key = key;
	this->pre = NULL;
	this->next = NULL;
}

/*******LRU*******/
LRU::LRU(int capacity) {
	this->capacity = capacity;
	this->num = 0;
	this->head = new Node(-1); // dummy node
	this->tail = this->head;
}

LRU::~LRU() {
	while (this->head != NULL) {
		Node * tmp = this->head;
		this->head = this->head->next;
		delete tmp;
	}
}

int LRU::access(int key) {
	if (this->keyNodemap.count(key) > 0) {
		Node * tmp = keyNodemap[key];
		this->updateToTail(tmp);
		return 1;
	}
	else {
		this->insert(key);
		return -1;
	}
}

void LRU::updateToTail(Node * node) {
	Node * left = node->pre;
	Node * right = node->next;
	if (right == NULL) return;  // right is NULL, already in tail

	left->next = right;
	right->pre = left;

	this->tail->next = node;
	node->pre = this->tail;
	node->next = NULL;
	this->tail = node;
}

void LRU::insert(int key) {
	if (this->num < this->capacity) {
		Node * cur = new Node(key);
		this->keyNodemap[key] = cur;
		this->num++;

		this->tail->next = cur;
		cur->pre = this->tail;
		this->tail = cur;
	} 
	else {
		this->evictOne();
		this->insert(key);
	}
}

void LRU::evictOne() {
	if (this->num <= 0) return;
	
	Node * target = this->head->next;

	this->head->next = target->next;

	if (this->tail != target) {
		target->next->pre = this->head;
	} else {
		this->tail = this->head;
	}
	this->num--;
	this->keyNodemap.erase(target->key);
	delete target;
}

void LRU::show() {
	Node * tmp = this->head;
	cout << "Head";
	for (int i = 0; i < this->num; i++) {
		tmp = tmp->next;
		cout << "->" << tmp->key;
	}
	cout << std::endl;
}