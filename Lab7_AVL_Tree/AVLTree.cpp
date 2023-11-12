#include <iostream>
#include "AVLTree.h"
#include <ostream>
#include <fstream>

using namespace std;

int AVLTree::height(Node* curr) {
    if (curr == nullptr) {
        return -1;
    }
    return max(height(curr->left), height(curr->right)) + 1;
}

int AVLTree::balanceFactor(Node* curr) {
    if (node == nullptr) { 
        return 0; 
    }
    return height(curr->left) - height(curr->right);
}

void AVLTree::insert(const string &newString) {
    if (root == nullptr) {  // edge case if tree is empty
        root = new Node(newString);
        return;
    }
    Node* curr = root;
    while (true) {
        if (curr->data == newString) { // if duplicate, then return
            break; 
        }
        if (newString < curr->data) { // go left
            if (curr->left == nullptr) { // if left child is empty, insert
                curr->left = new Node(newString);
                curr->parent = curr;
                break;
            }
            curr = curr->left;
        }
        else { // go right
            if (curr->right == nullptr) { // if right child is empty, insert
              curr->right = new Node(newString);
              curr->parent = curr;
              break;
            }
            curr = curr->right;
        }
    }
    while (curr != nullptr) {
        if (balanceFactor(curr) > 1 || balanceFactor(curr) < -1) {
            rotate(curr);
        }
        // move up tree
        curr = curr->parent;
    }
}

void AVLTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout << "Error" << endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS<< n->data << " -> " << n->left->data << ";" << endl;    
        }

        if(n->right){
            visualizeTree(outFS,n->right);
            outFS<< n->data << " -> " << n->right->data<< ";" <<endl;    
        }
    }
}

void AVLTree::printBalanceFactors(){
    printBalanceFactors(root); //call private helper from root
}

void AVLTree::printBalanceFactors(Node *curr){
    if(curr != nullptr){
        //recrusively travel left then print and travel right so its in order
        printBalanceFactors(curr->left);
        cout << curr->data 
             << "(" << balanceFactor(curr) << ")"
             << ", ";
        printBalanceFactors(curr->right);
    }
    else{
        // throw runtime_error("printing empty root");
        return;
    }
}




