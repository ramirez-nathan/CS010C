#ifndef __TREE_H
#define __TREE_H

#include "Node.h"

class Tree {
private:
  Node *root;

public:
  Tree() : root(nullptr) 
  {
  }
  ~Tree( );
  void insert(const string &);
  void preOrder( ) const;
  void inOrder( ) const;
  void postOrder( ) const;
  void remove(const string &);
  bool search (const string &) const;

private:
  // Add additional functions/variables here
  void insert(const string &, Node*);
  void TreeSplit(Node*, const string &);
  void preOrder(Node*) const;
  void inOrder(Node*) const;
  void postOrder(Node* ) const;
  void remove(const string &, Node*); // private recursive helper function
  bool search(const string &, const Node*) const;
  Node* searchNode(const string &, Node*); 
  void destructor(Node*);

  // Rule of 3  
  Tree & operator=(const Tree &) = delete;
  Tree(const Tree &copy) = delete;
  
};

#endif