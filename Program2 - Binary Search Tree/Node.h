#include <iostream>
#ifndef __NODE_H__
#define __NODE_H__

using namespace std;

struct Node { // we use struct here because POD ("plain old data")
    string data;
    int count;
    Node* left;
    Node* right;
  Node (const string& key) 
    :
    data(key),
    count(1),
    left(nullptr),
    right(nullptr)
  {
  }
};



#endif