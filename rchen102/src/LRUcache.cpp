#include "../include/LRUcache.h"

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

/*******LRUcache*******/
LRUcache::LRUcache(int capacity) {
	this->capacity = capacity;
	this->num = 0;
	this->head = new Node(-1); // dummy node
	this->tail = this->head;
}

LRUcache::~LRUcache() {
	while (this->head != NULL) {
		Node * tmp = this->head;
		this->head = this->head->next;
		delete tmp;
	}
}

void LRUcache::access(int key) {
	if (this->keyNodemap.count(key) > 0) {
		Node * tmp = keyNodemap[key];
		this->updateToTail(tmp);
	}
	else {
		this->insert(key);
	}
}

void LRUcache::updateToTail(Node * node) {
	Node * left = node->pre;
	Node * right = node->next;
	if (right == NULL) return;  // right is NULL, already in tail

	left->next = right;
	right->pre = left;

	this->tail->next = node;
	node->pre = this->tail;
	this->tail = node;
}

void LRUcache::insert(int key) {
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

void LRUcache::evictOne() {
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

void LRUcache::show() {
	Node * tmp = this->head;
	cout << "Head";
	for (int i = 0; i < this->num; i++) {
		tmp = tmp->next;
		cout << "->" << tmp->key;
	}
	cout << std::endl;
}