#include <iostream>
#include <stdexcept>
#include "PrintJob.h"
#include "Heap.h"

using namespace std;

// Delete all elements in Heap
// 1) Iterate and delete last element each loop (size - 1)
// 2) Decrement size for each loop
Heap::~Heap(){
  while (numItems > 0) { // iterate until all elements are deleted
    // delete last item and decrement size
    delete arr[numItems - 1]; 
    --numItems;
  }
}

void Heap::enqueue(PrintJob * newItem) {
  if (numItems >= MAX_HEAP_SIZE) {// edge case if heap is full {
    throw runtime_error("Can't enqueue on full Heap");
    // return; // for zybooks submission
  }
  else {
    // add new item to array and then call percolateUp to put it in correct position
    arr[numItems] = newItem;
    percolateUp(numItems, arr);
    ++numItems;
  }

}

void Heap::percolateUp(int Index, PrintJob* heapArray[]) {
  while (Index > 0) { // while index is not root
    int parIndex = (Index - 1) / 2; // parent index
    // edge case if item priority is already correct
    if (heapArray[Index]->getPriority() <= heapArray[parIndex]->getPriority()) {
      return;
    }
    else { // swap item with parent 
      swap(heapArray[Index], heapArray[parIndex]);
      Index = parIndex;
    }
  }
}

PrintJob* Heap::highest() const {
  if (numItems == 0) { // edge case if heap is empty
    return nullptr;
  }
  else { // return root (highestpriority)
    return arr[0];
  }
}

void Heap::print(){
  //edge case for printing less than 0 items in array
  if(numItems <= 0){
      throw runtime_error("empty");
  }
  else{
  //print object's data fields
      cout << "Priority: " << highest()->getPriority() << ", "
           << "Job Number: " << highest()->getJobNumber() << ", "
           << "Number of Pages: " << highest()->getPages() << endl;
  }
}

void Heap::dequeue() {
  if (numItems == 0) { // edge case if empty
    throw runtime_error ("Could not dequeue on empty array.");
    // return; // for zybooks submission
  }
  if (numItems == 1) { // edge case if size is 1 then print the root
    delete arr[0];
    numItems--;
    return;
  }

  // Identify last leaf node
  // 1) Identify last INTERNAL node (n/2 - 1)
  // 2) Look right. If right, then thats the answer
  // 3) Else, assume left

  // find last internal node
  int last_inode = numItems / 2 - 1;
  
  PrintJob* left = arr[2 * last_inode + 1];
  PrintJob* right = arr[2 * last_inode +2];

  // check right, then swap with root
  if (right) {
    PrintJob* victim = arr[0];
    swap(arr[0], right);
    delete victim;
  }
  // else left, then swap with root
  else {
    PrintJob* victim = arr[0];
    swap(arr[0], left);
    delete victim;
  }

  numItems--;

  trickleDown(0); 
}

void Heap::trickleDown(int Index) {
  PrintJob* curr = arr[Index];
  PrintJob* left = arr[2*Index + 1];
  PrintJob* right = arr[2*Index + 2];
  // if current index is a leaf, then return
  if ((left == nullptr) && (right == nullptr)) {
    return;
  }
  // not a leaf, try to trickle down
  
  if (left && right) { // if node has left and right
      // if left is greater then swap with left
      if (left->getPriority() > right->getPriority()) { 
          swap(curr, left);
          trickleDown(2 * Index + 1);
      }
      else { // else swap with right
          swap(curr, right);
          trickleDown(2 * Index + 2);
      }
  }
  else { // if only has left
      if (left->getPriority() > curr->getPriority()) {
        swap(curr, left);
        trickleDown(2 * Index + 1);
      }
  }
  // There can't be just a right child because a heap must be completed
}