#ifndef __BSTREE_H__
#define __BSTREE_H__


#include <iostream>
#include "Node.h"
using namespace std;

class BSTree {
  public:
    // Default constructors
    BSTree() : root(nullptr) {}
    // Destructor
    ~BSTree();

    // Mutators
    /* 
          Insert item into BST 
    *Be sure to maintain BST properties*
      1) If item is first inserted set its count to 1
      2) If item is duplicate string (case sensitive) then increment node and return
    */
    void insert(const string& newString);

    void remove(const string& key);
  
    // Accessors 
    bool search(const string& key) const;

    string largest() const;
    string smallest() const;
    
    int height(const string&) const;

    // Printing 
    /* For all printing orders, each node should be displayed as follows:
       <string> (<count>)
       e.g. goodbye(1), Hello World(3)
    */
    void preOrder() const;
    void postOrder() const;
    void inOrder() const;


    
  private:
    Node* root; 

    /* Private helper functions below */ 

    /*
            Remove a specified string from the tree
      1) If empty, return empty
      2) If key matches me 
          a) If count > 1 : decrement count, return same tree (edge case)
          b) Count == 1 (where rest of the if statements continue)
              i) If leaf (no children): delete me, return nullptr
              ii) If only left child : delete me, return left child
                  Lets find the predecessor
                  • Find victim (rightmost node in left subtree)
                  • Copy victim's info to me
                  • Replace my left subtree with remove(my left subtree, victim's key)
                  • Return me
              iii) If only right child, delete me, return right child
                  Lets find the successor
                  • Find victim (leftmost node in right subtree)
                  • Copy victim's info to me
                  • Replace my right subtree with remove(my right subtree, victim's key)
                  • Return me
              iv) Else (it has left and right child) 
                  Lets find the predecessor
                  • Find victim (rightmost node in left subtree)
                  • Copy victim's info to me
                  • Replace my left subtree with remove(my left subtree, victim's key)
                  • Return me
      3) If key is in left subtree 
          my left = remove(key, left subtree)
          return me
      4) If key is in right subtree
          my right = remove(key, right subtree)
          return me
    */
    Node* remove(Node*, const string&);

    /*
          Search for a string and return true if it exists, otherwise return false
      // wrote search function for the Midterm.. this is what it was
      Node* curr = root; // unnecessary in this case because of parameter passing
      while (curr != nullptr) {
        if (curr->value == key) { //found it
          return true;
        }
        if (key < curr->value) {  //go left
          curr = curr->left;
        }
        else { //go right
          curr = curr->right;
        }
      }
      return false;
      // TODO: tweak it up so it works here 
    */
    bool search(const Node*, const string&) const;
    /* Find and return the largest value in the tree. Return an empty string if the tree is empty */
    string largest(const Node*) const;
    /* Find and return the smallest value in the tree. Return an emtpy string if the tree is empty */
    string smallest(const Node*) const;
    /* Compute and return the height of a particular string in the tree. 
       The height of a leaf node is 0 (count the number of edges on the longest path). 
       Return -1 if the string does not exist. 
     */
    int height(const Node *root) const;
    // Helper for height function
    int goDown(const Node* curr) const;

    void preOrder(const Node*) const; 
    void postOrder(const Node*) const;
    void inOrder(const Node*) const;

    /* private destructor helper function */
    void Destructor(Node* root);
    
    
    



};


#endif