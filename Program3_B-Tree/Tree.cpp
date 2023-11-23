#include <iostream>
#include "Tree.h"


using namespace std;

Tree::~Tree( ){
    destructor(root);
}
void Tree::destructor(Node* curr){
    //private helper to destroy 
    if(curr == nullptr){ //base case
        return;
    }
    //traverse to last node then start deleting
    destructor(curr->left);
    destructor(curr->middle);
    destructor(curr->right);

    delete curr;
}

void Tree::preOrder() const{
    preOrder(root);
}
void Tree::preOrder(Node *curr) const{
    if(curr == nullptr){
        return;
    }
    else{
        if(curr->countData == 1){ //if only one key
        //then output then recurisvely traverse left then right
            cout << curr->small << ", ";
            preOrder(curr->left);
            preOrder(curr->right);
        }
        else if(curr->countData == 2){ // edge case for two keys in a node
        //output small key first then traverse left and print same node large key 
            cout << curr->small << ", ";
            preOrder(curr->left);
            cout << curr->large << ", ";
            preOrder(curr->middle);
            preOrder(curr->right);
        }
    }
}
void Tree::inOrder() const{
    inOrder(root);
}
void Tree::inOrder(Node *curr) const{
    if(curr == nullptr){
        return;
    }
    else{
        if(curr->countData == 1){ //edge case for 1 key in node
            inOrder(curr->left);
            cout << curr->small << ", ";
            inOrder(curr->right);
        }
        else if(curr->countData == 2){ //edge case for 2 keys in node
            inOrder(curr->left);
            cout << curr->small << ", ";
            inOrder(curr->middle);
            cout << curr->large << ", ";
            inOrder(curr->right);
        }
    }
}

void Tree::postOrder() const{
    postOrder(root);
}
void Tree::postOrder(Node *curr) const{
    if(curr == nullptr){
        return;
    }
    else{
        if(curr->countData == 1){ //edge case for 1 key in node
        //travel to last then start outputting
            postOrder(curr->left);
            postOrder(curr->right);
            cout << curr->small << ", ";
        }
        else if(curr->countData == 2){ //edge case for 2 keys in node
        //traverse to middle first then start outputting
            postOrder(curr->left);
            postOrder(curr->middle);
            cout << curr->small << ", ";
            postOrder(curr->right);
            cout << curr->large << ", ";
        }
    }
}


