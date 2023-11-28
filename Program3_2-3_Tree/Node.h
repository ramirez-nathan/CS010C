#ifndef __NODE_H
#define __NODE_H

#include <string>

using namespace std;

struct Node { // all POD - make a struct

  friend class Tree;

    string small;
    string large;
    int keyCount; 

    Node *left;
    Node *middle;
    Node *right;
    Node *parent;


    Node (const string& key)  
    :
    small(key),
    large(""), // Set as an empty string because when u create a new node it will be just 1 key most times
    keyCount(1),
    left(nullptr),
    middle(nullptr),
    right(nullptr),
    parent(nullptr)
    {
    } 
  // Add additional functions/variables here. Remember, you may not add any
  // Node * or string variables.

};

#endif