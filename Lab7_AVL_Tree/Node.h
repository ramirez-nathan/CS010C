#ifndef NODE_H
#define NODE_H
#include <iostream>

using namespace std;

struct Node { // we use struct here because POD ("plain old data")
    string data;
    Node* parent;
    Node* left;
    Node* right;
  Node (const string& value) 
    :
    data(value),
    parent(nullptr),
    left(nullptr),
    right(nullptr)
  {
  }
};



#endif