#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
#include "Node.h"

using namespace std;

class AVLTree {
    public:
        AVLTree() : root(nullptr) 
        {
        }

        
        void insert(const string &); // Insert an item to the binary search tree and perform rotation if necessary

        int balanceFactor(Node* curr) { return (height(curr->left) - height(curr->right)); } // Return the balance factor of a given node

        void printBalanceFactors(); // Traverse and print the tree in inorder notation. Print the string followed by its balance factor in parentheses followed by a , and one space.

        void visualizeTree(const string &); 

    private:

        Node* root;
        void rotate(Node* );
        void rotateLeft(Node *);
        void rotateRight(Node *);
        void replaceChild(Node* , Node* , Node* );
        void setChild(Node *, const string &, Node* );
        void insert(const string &key, Node* curr);
        void printBalanceFactors(Node *);
        int height(Node *);
        void visualizeTree(ofstream &, Node *);

        
        
};

#endif