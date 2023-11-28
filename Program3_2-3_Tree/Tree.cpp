#include <iostream>
#include "Tree.h"


using namespace std;

Tree::~Tree( ) {
    destructor(root);
}
void Tree::destructor(Node* curr) {
    //private helper to destroy 
    if(curr == nullptr) { //base case
        return;
    }
    //traverse to last node then start deleting
    destructor(curr->left);
    destructor(curr->middle);
    destructor(curr->right);

    delete curr;
}

void Tree::preOrder() const {
    preOrder(root);
}
void Tree::preOrder(Node *curr) const {
    if(curr == nullptr) {
        return;
    }
    else{
        if(curr->keyCount == 1) { //if only one key
        //then output then recurisvely traverse left then right
            cout << curr->small << ", ";
            preOrder(curr->left);
            preOrder(curr->right);
        }
        else if(curr->keyCount == 2) { // edge case for two keys in a node
        //output small key first then traverse left and print same node large key 
            cout << curr->small << ", ";
            preOrder(curr->left);
            cout << curr->large << ", ";
            preOrder(curr->middle);
            preOrder(curr->right);
        }
    }
}
void Tree::inOrder() const {
    inOrder(root);
}
void Tree::inOrder(Node *curr) const {
    if(curr == nullptr) {
        return;
    }
    else {
        if(curr->keyCount == 1){ //edge case for 1 key in node
            inOrder(curr->left);
            cout << curr->small << ", ";
            inOrder(curr->right);
        }
        else if(curr->keyCount == 2){ //edge case for 2 keys in node
            inOrder(curr->left);
            cout << curr->small << ", ";
            inOrder(curr->middle);
            cout << curr->large << ", ";
            inOrder(curr->right);
        }
    }
}

void Tree::postOrder() const {
    postOrder(root);
}
void Tree::postOrder(Node *curr) const {
    if(curr == nullptr){
        return;
    }
    else{
        if(curr->keyCount == 1) { //edge case for 1 key in node
        //travel to last then start outputting
            postOrder(curr->left);
            postOrder(curr->right);
            cout << curr->small << ", ";
        }
        else if(curr->keyCount == 2) { //edge case for 2 keys in node
        //traverse to middle first then start outputting
            postOrder(curr->left);
            postOrder(curr->middle);
            cout << curr->small << ", ";
            postOrder(curr->right);
            cout << curr->large << ", ";
        }
    }
}

void Tree::insert(const string &key) {
    if (root == nullptr) { // edge case for when tree is empty
        Node* newNode = new Node(key);
        root = newNode;
    } 
    else { 
        insert(key, root); // call private helper
    }
}

void Tree::insert(const string &key, Node* curr) {
    if (curr == nullptr) { // base case for recursion
        return;
    }

    if(key < curr->small){ // edge case for when key is smaller than both keys
        if(curr->keyCount == 1){
            if(curr->left == nullptr){
                curr->large = curr->small;
                curr->small = key;
                ++curr->keyCount; 
            }
            else{
                insert(key, curr->left);
            }
        }
        else if(curr->keyCount == 2){
            if(curr->left != nullptr){
                insert(key,curr->left);
            }
            else{
                TreeSplit(curr, key);
            }
        }
        else{
            TreeSplit(curr, key);
        }
    }
    else if(key > curr->small){ // when key either in between or bigger than curr
        if(curr->keyCount == 1){ //check how many are in curr
            if(curr->right == nullptr){  //if at leaf then insert as large key in curr
                curr->large = key;
                ++curr->keyCount;
            }
            else{
                insert(key,curr->right); //else branch to the right
            }
        }
        else if(curr->keyCount == 2 && key < curr->large){ // when key is bigger than both in curr
            if(curr->middle != nullptr){ // recursively call insert to insert in the middle
                insert(key, curr->middle);
            }
            else{ // else lost so split
                TreeSplit(curr, key);
            }
        }
        else{
            TreeSplit(curr, key);
        }
    }
}

void Tree::TreeSplit(Node* curr, const string &key) {
    Node *leftChild = nullptr;
    Node *rightChild = nullptr;
    string middleKey = "";

    if(curr->large == ""){ //base case for splitting
        return;
    }
    if(key == curr->small || key == curr->large){ // edge case for duplicates
        throw runtime_error("duplicate");
    }
    // setting the left, middle, and right to prepare for split
    if(key < curr->small){ // edge case for when the key is smaller than both keys in curr
        leftChild = new Node(key);
        rightChild = new Node(curr->large);
        middleKey = curr->small;

        
    }
    else if(key > curr->large){ //edge case for when the key is larger than both keys in curr
        leftChild = new Node(curr->small);
        middleKey = curr->large;
        rightChild = new Node(key);


    }
    else{ //when key is in between
        leftChild = new Node(curr->small);
        middleKey = key;
        rightChild = new Node(curr->large);

    }
    // making the current node a single key to prepare for split
    curr->large = "";
    --curr->keyCount;

    if(curr->parent != nullptr){ // edge case for when the node has parents
        //promote middleKey to parent large key 
        curr->parent->large = middleKey;
        ++curr->parent->keyCount;
        // previous left and right child become middle and right child
        curr->parent->middle = leftChild;
        leftChild->parent = curr->parent;
        curr->parent->right = rightChild;
        rightChild->parent = curr->parent;
    }
    else{ 
        //making middleKey parent of leftchild and right child
        curr->small = middleKey;
        curr->left = leftChild;
        curr->right = rightChild;
        leftChild->parent = curr;
        rightChild->parent = curr;
    }
}

void Tree::remove(const string &key){

    remove(key, root);
}

void Tree::remove(const string &key, Node* curr){
    if(curr == nullptr){
        return;
    }
    //check if node exists
    if(search(key, curr)){
        //find the node containing key
        curr = searchNode(key, curr); // need a Node* helper function version of search
        //if node is root
        if(curr->parent == nullptr){
            //if a leaf
            if(curr->left == nullptr && curr->right == nullptr){
                //if only 1 key inside
                if(curr->keyCount == 1){
                    delete curr;
                    root = nullptr;
                }
                //more than 1 key
                else{
                    //check to see which key is the key we are trying to remove
                    if(curr->small == key){
                        curr->small = curr->large;
                        curr->large = "";
                        --curr->keyCount;
                    }
                    else if(curr->large == key){
                        curr->large = "";
                        --curr->keyCount;
                    }
                }
            }
            else{ //node has children
                curr->small = curr->left->small;
                curr->large = curr->right->small;
                ++curr->keyCount;
                delete curr->right;
                delete curr->left;
                curr->right = nullptr;
                curr->left = nullptr;

            }
        }
        else{ //node is not root
            if(curr->keyCount == 1){ // node has one key
                Node *par = curr->parent;
                if(par->right == curr){  //node is right child of parent
                    par->large = par->small;
                    par->small = par->left->small;
                }
                else if(par->left == curr){ //node is left child
                    par->large = par->right->small;
                }
                ++par->keyCount;
                delete par->left;
                delete par->right;
                par->left = nullptr;
                par->right = nullptr;
            }
            else{ // more than one key
                if(curr->small == key){ //in case the small field
                    curr->small = curr->large;
                }
                --curr->keyCount;
                curr->large = "";         
            }
        }
    }
}

bool Tree::search(const string &key) const {
    return search(key, root);
}

bool Tree::search(const string &key, const Node* curr) const {
    if (curr == nullptr) { //if empty
        return false;
    }
    if (curr->small == key || curr->large == key) { //if key found return true
        return true;
    }
    else{
        if(key < curr->small){
            return search(key, curr->left); //traverse left
        }
        else if(curr->keyCount == 2 && key < curr->large){
            return search(key, curr->middle); //traverse down the middle
        }
        else{
            return search(key, curr->right); //traverse right
        }
    }
}
// SAME FUNCTION AS SEARCH, JUST RETURNS A NODE INSTEAD OF A BOOLEAN
Node* Tree::searchNode(const string &key, Node* curr) {
    if(curr == nullptr){ //if empty
        return nullptr;
    }
    if(curr->small == key || curr->large == key){ //if key found return the node
        return curr;
    }
    else{
        if(key < curr->small){
            return searchNode(key, curr->left); //traverse left
        }
        else if(curr->keyCount == 2 && key < curr->large){
            return searchNode(key, curr->middle); //traverse down the middle
        }
        else{
            return searchNode(key, curr->right); //traverse right
        }
    }
}

