#include <ostream>
#include <string>
#ifndef IntList_h
#define IntList_h
using namespace std;

struct IntNode {
    int data;
    IntNode *prev;
    IntNode *next;
    IntNode(int data) : data(data), prev(0), next(0) {}
};

class IntList {
  public: 
    IntList() { // initializes our dummyHead and dummyTail
      dummyHead = new IntNode(0);
      dummyTail = new IntNode(0);
    
      dummyHead->next = dummyTail;
      dummyTail->prev = dummyHead;
    }
  
    ~IntList();
  
    void push_front(int value); 
  
    void pop_front(); 
    
    void push_back(int value);
    
    void pop_back();
  
    bool empty() const; 
    
    friend ostream & operator<<(ostream &out, const IntList &rhs);
  
    void printReverse() const;

  private:
    IntNode* dummyHead;
    IntNode* dummyTail;
    IntList(const IntList &copy) = delete;
    IntList & operator=(const IntList &) = delete;
};
#endif


