#pragma once

#include <iostream>
#include "stack.h"
#include <stdexcept>
#include <string>

const int MAX_SIZE = 20;
using namespace std;

template <typename T> 
class stack {
public:
  // constuct an empty stack
  stack() { size = 0; }
  // inserts a new element to the top of the stack
  void push(const T &val) {
    ++size;
    // if size is less than or equal to max size
    if (size <= MAX_SIZE) {
      data[size - 1] = val;
    }
    // edge case if stack is full
    else {
      throw overflow_error("Called push on full stack.");
    }
  }
  // remove top element from stack
  void pop() {
    if (!empty()) {
      --size;
    }
    // edge case if empty
    else {
      throw overflow_error("Called pop on empty stack.");
    }
  }

  void pop_two() {
    // if stack size is greater than or equal to 2 then decrement by 2
    if (size >= 2) {
      size -= 2;
    }
    // edge case if size is 1
    else if (size == 1) {
      throw out_of_range("Called pop_two on a stack of size 1.");
    }
    // edge case if stack is empty
    else {
      throw out_of_range("Called pop_two on an empty stack.");
    }
  }
  T top() const {
    // return top element if stack is not empty
    if (!empty()) {
      return data[size - 1];
    }
    // edge case if stack is empty
    else {
      throw underflow_error("Called top on empty stack.");
    }
  }
  // check if stack is empty 
  bool empty() const {
    return size == 0;
  }


private:
  T data[MAX_SIZE];
  int size;
};