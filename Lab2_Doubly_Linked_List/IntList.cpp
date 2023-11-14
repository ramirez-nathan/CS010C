#include <iostream>
#include <string>
#include <exception>
#include "IntList.h"
using namespace std;


IntList::~IntList() { // Destructor, deallocates all remaining dynamically allocated memory (all the remaining IntNodes)
  IntNode* curr = dummyHead;
  while (curr != dummyHead) {
      IntNode* temp = curr;
      curr = curr->next;
      delete temp;
  }
}

void IntList::push_front(int value) { // Inserts a data value (within a new node) at the front end of the list (O(1) operation)
  IntNode* newNode = new IntNode(value);
  IntNode* dummyNext = dummyHead->next; // while dummyHead and dummyTail are placeholders, adding dummyNext allows the program to more easily find certain values. dummyNext actually goes through the values.
  
  dummyHead->next = newNode;
  dummyNext->prev = newNode; 
  newNode->next = dummyNext;
  newNode->prev = dummyHead;
  
}

void IntList::pop_front() { // Removes the node at the front end of the list (the node after the dummy head). Does nothing if the list is already empty
  if (empty() == true) {
    throw runtime_error("List was empty");
  }
  else {
    IntNode* temp = dummyHead->next;
    dummyHead->next = temp->next;
    temp->next->prev = dummyHead;
    delete temp;
  }
}

void IntList::push_back(int value) { // inserts data value (within a node) at back of list (O(1))
  IntNode* addNode = new IntNode(value);
  IntNode* prevDummyTail = dummyTail->prev;

  dummyTail->prev = addNode;
  addNode->next = dummyTail;
  prevDummyTail->next = addNode;
  addNode->prev = prevDummyTail;

}

void IntList::pop_back() { // remove node at back end of list (node before dummyTail). Does nothing if list is empty.
  if (empty() == true){
    throw runtime_error("List was empty");
  }
  else {
    IntNode* temp = dummyTail->prev;
    dummyTail->prev = temp->prev;
    temp->prev->next = dummyTail;
    delete temp;
    
  }
}

bool IntList::empty() const { // Returns true if the list does not store any data values (it only has dummy head and dummy tail), otherwise returns false
  return dummyHead->next == dummyTail && dummyTail->prev == dummyHead;
}

ostream & operator<<(ostream &out, const IntList &rhs) { // outputs to the stream all of the integer values within the list on a single line
  IntNode* current = rhs.dummyHead->next;
  if (rhs.empty() == true) {
    throw runtime_error("List was empty");
  }
  else if (current->next == rhs.dummyTail) {
    out << current->data;
    return out; 
  }
  else {
    while (current != nullptr) {
      if (current->next == rhs.dummyTail) {
        out << current->data;
        break;
      }
      else {
        out << current->data << " ";
      }
      current = current->next;
    }  
  }
  return out;
}

void IntList::printReverse() const {
    IntNode* node = dummyTail->prev;
    if (empty() == true) {
      throw runtime_error("List was empty");
    }
    else if (node->prev == dummyHead) {
      cout << node->data;
      return;
    }
    else {
      while (node != nullptr) {
        if (node->prev == dummyHead) {
          cout << node->data;
          break;
        }
        else {
          cout << node->data << " ";
        }
        node = node->prev;
      }  
    }
}

