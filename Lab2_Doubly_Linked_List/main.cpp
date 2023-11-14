#include "IntList.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
  IntList newList;

  newList.push_back(11);
  newList.push_back(22);
  newList.push_front(33);
  newList.push_front(44);
  // list is 44, 33, 11, 22
  newList.pop_front(); // this removes node at front of list (44)

  newList.pop_back(); // this removes node at back of list (22)
  newList.printReverse(); // this prints the list in reverse order
  
  return 0;
}