#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <list>
#include <iostream>
#include "WordEntry.h"

using namespace std;

class HashTable {

 private:
	list<WordEntry> *hashTable;
	int size;

 public:
	HashTable(int);
	~HashTable();
	bool contains(const string &);
	double getAverage(const string &);
	void put(const string &, int);
 
 private:
	int computeHash(const string &);

	HashTable(const HashTable &copy) = delete; // copy constructor
	HashTable & operator=(const HashTable &copy) = delete; // copy asssingment 
};

#endif