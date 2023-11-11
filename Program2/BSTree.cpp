#include <iostream>
#include "Node.h"
#include "BSTree.h"

using namespace std;

BSTree::~BSTree() {
    Destructor(root); // calls private helper function
}

// private Destructor helper function
void BSTree::Destructor(Node* curr) {
    if (curr == nullptr) { // edge case if tree is empty
        return;
    }
    Destructor(curr->left);
    Destructor(curr->right);
    delete curr;
}

// inserts a new string into the tree
void BSTree::insert(const string& newString) {
    if (root == nullptr) {  // edge case if tree is empty
        root = new Node(newString);
        return;
    }
    Node* curr = root;
    while (true) {
        if (curr->data == newString) { // if duplicate, then increment count and return
            ++curr->count;
            return; 
        }
        if (newString < curr->data) { // go left
            if (curr->left == nullptr) { // if left child is empty, insert
                curr->left = new Node(newString);
                return;
            }
            curr = curr->left;
        }
        else { // go right
            if (curr->right == nullptr) { // if right child is empty, insert
              curr->right = new Node(newString);
              return;
            }
            curr = curr->right;
        }
    }
}

// removes a specified string from the tree
void BSTree::remove(const string& newString) {
    root = remove(root, newString); // call private helper function
}

// private helper function 
Node* BSTree::remove(Node* curr, const string& key) {
    if (curr == nullptr) { // edge case if tree is empty, return empty (nullptr)
        return nullptr;
    }
    else if (curr->data == key) { // if key matches curr->data
        if (curr->count > 1) { // edge case if count > 1, decrement count and return same tree
            --curr->count;
            return curr;
        }
        if (curr->left == nullptr && curr->right == nullptr) { // if leaf, delete curr and return nullptr
            delete curr;
            return nullptr;
        }
        else if (curr->right == nullptr) { // if only left child
          // find the biggest child in the left subtree
          Node* victim = curr->left; // go to left subtree
          while (victim->right != nullptr) { // go right until youre "about to fall off the tree", to the biggest child 
              victim = victim->right; 
          }
          // Copy victim's info to curr->data
          curr->data = victim->data; 
          curr->count = victim->count;
          victim->count = 1; // set victim's count to 1 so remove() actually deletes the node
          curr->left = remove(curr->left, victim->data);
          return curr;
        }
        else if (curr->left == nullptr) { // if only right child
          // find the biggest child in the left subtree
          Node* victim = curr->right; // go to left subtree
          while (victim->left != nullptr) { // go right until youre "about to fall off the tree", to the biggest child 
              victim = victim->left; 
          }
          // Copy victim's info to curr->data
          curr->data = victim->data; 
          curr->count = victim->count;
          victim->count = 1; // set victim's count to 1 so remove() actually deletes the node
          curr->right = remove(curr->right, victim->data);
          return curr;
        }
        else { // if it has both right and left childen
            // find the biggest child in the left subtree
              Node* victim = curr->left; // go to left subtree
              while (victim->right != nullptr) { // go right until youre "about to fall off the tree", to the biggest child 
                  victim = victim->right; 
              }
              // Copy victim's info to curr->data
              curr->data = victim->data; 
              curr->count = victim->count;
              victim->count = 1; // set victim's count to 1 so remove() actually deletes the node
              curr->left = remove(curr->left, victim->data);
              return curr;
        }
    }
    else if (key < curr->data) { // if key is in left subtree 
      curr->left = remove(curr->left, key); 
      return curr;
    }
    else { // else key is in right subtree
      curr->right = remove(curr->right, key);
      return curr;
    }
}

// searches for a specified string in the tree and returns true if it exists, otherwise returns false
bool BSTree::search(const string& key) const {
    return search(root, key); // calls private helper
}

// search's private helper function
bool BSTree::search(const Node* curr, const string& key) const {
    while (curr != nullptr) {
      if (curr->data == key) { //found it
        return true;
      }
      if (key < curr->data) {  //go left
        curr = curr->left;
      }
      else { //go right
        curr = curr->right;
      }
    }
    return false;
}

// finds and returns largest value in the tree
string BSTree::largest() const {
    if (root == nullptr) { // edge case if tree is empty, return empty string
        return "";
    }
    else {
        return largest(root); // call recursive helper
    }
}
// largest private helper function
string BSTree::largest(const Node* curr) const {
    while (true) {
        if (curr->right == nullptr) { // if at left end of tree, return curr->data
            return curr->data;
        }
        else {
            curr = curr->right; // else go left 
        }
    }
}

// finds and returns smallest value in the tree
string BSTree::smallest() const {
    if (root == nullptr) { // edge case if tree is empty, return empty string
        return "";
    }
    else {
        return smallest(root); // call recursive helper
    }
}
// smallest private helper function
string BSTree::smallest(const Node* curr) const {
    while (true) {
        if (curr->left == nullptr) { // if at left end of tree, return curr->data
            return curr->data;
        }
        else {
            curr = curr->left; // else go left 
        }
    }
}

// takes a key and returns the height of the node with that key in the BST
int BSTree::height(const string& key) const { 
    Node* curr = root;
    while (curr != nullptr) { // loops until key is found
        if (curr->data == key) { // found it, break loop
            break;
        }
        else if (key < curr->data) { // go left if key is less than curr->data
            curr = curr->left;
        }
        else { // else go right if key is greater than curr->data
            curr = curr->right;
        }
    }
    return goDown(curr); // calls private helper
}

// private helper function for height
int BSTree::goDown(const Node* curr) const {
    if (curr == nullptr) { // edge case if node is null, return -1
        return -1;
    }
    int leftHeight = goDown(curr->left); // get height of left subtree
    int rightHeight = goDown(curr->right); // get height of right subtree
  
    return max(leftHeight, rightHeight) + 1; // compares left and right subtrees' height, gets largest value, plus 1 for curr node
}

// Traverses tree in pre-order and prints each node's data and count
void BSTree::preOrder() const{
    preOrder(root);
}

void BSTree::preOrder(const Node *curr) const{
    if (curr != nullptr) {
        cout << curr->data << "(" << curr->count << "), "; // print the current node
        preOrder(curr->left); // traverse left subtree
        preOrder(curr->right); // traverse right subtree
    }
    else { // else if node is null, return
        return;
    }
}

// Traverses the tree in post-order and prints each node's data and count
void BSTree::postOrder() const{
    postOrder(root);
}

void BSTree::postOrder(const Node* curr) const{
    if(curr != nullptr){
        postOrder(curr->left); // traverse left subtree
        postOrder(curr->right); // traverse right subtree
        cout << curr->data << "(" << curr->count << "), "; // output data
    }
    else { // else if node is null, return
        return;
    }
}

// Traverses the tree in in-order and prints each node's data and count
void BSTree::inOrder() const{
    inOrder(root);
}

void BSTree::inOrder(const Node* curr) const{
    if (curr != nullptr) {
        inOrder(curr->left);
        //output data
        cout << curr->data << "(" << curr->count << "), ";
        //traverse right
        inOrder(curr->right);

    }
    else { // else if node is null, return
        return;
    }
}

