#include <iostream>
#include <algorithm>
#include <ctime>


using namespace std;

const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; //clock per milliseconds
const int NUMBERS_SIZE = 50000;



int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}

void fillArrays(int arr1[], int arr2[],int arr3[]){
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

void Quicksort_midpoint(int numbers[], int i, int k) {
    if(i >= k){ //base case
        return;
    }
    int pivot = numbers[i + (k - i) / 2]; //pivot is the middle index
    int lowIndex = i;
    int highIndex = k;

    bool done = false;
    
    while(!done){ // loop until one or no elements left,
        //increment while the numbers are less than the pivot
        while(numbers[lowIndex] < pivot){
            ++lowIndex;
        }
        //decrement while numbers are more than the pivot
        while(numbers[highIndex] > pivot){
            --highIndex;
        }
        //partitioning is done so break 
        if(lowIndex >= highIndex){
            done = true;
            break;
        }
        else{
            //else swap low and high index 
            int temp = numbers[highIndex];
            numbers[highIndex] = numbers[lowIndex];
            numbers[lowIndex] = temp;

            ++lowIndex;
            --highIndex; 
        }
    }
    //recursively sort lower and higher partition
    Quicksort_midpoint(numbers,i,highIndex);
    Quicksort_midpoint(numbers,highIndex + 1, k);

}

//helper function to find median
int median(int a, int b, int c){
    if(a < b){
        if(b < c){
            return b;
        }
        else if(a < c){
            return c;
        }
        else{
            return a;
        }
    }
    else{
        if(a < c){
            return a;
        }
        else if(b < c){
            return c;
        }
        else{
            return b;
        }
    }
}

void Quicksort_medianOfThree(int numbers[], int i, int k) {
    if(i >= k){ //base case, if array is sorted or none to sort
        return;
    }
    int pivot = median(numbers[i], numbers[i + ((k - i) / 2)], numbers[k]);
    int lowIndex = i;
    int highIndex = k;

    bool done = false;
    
    while(!done){ //loop until one or none elements left
        //increment while the numbers are less than the pivot
        while(numbers[lowIndex] < pivot){
            ++lowIndex;
        }
        //decrement while numbers are more than the pivot
        while(numbers[highIndex] > pivot){
            --highIndex;
        }
        //then partitioning is done so break 
        if(lowIndex >= highIndex){
            done = true;
            break;
        }
        else{
            //else swap low and high index 
            int temp = numbers[highIndex];
            numbers[highIndex] = numbers[lowIndex];
            numbers[lowIndex] = temp;

            ++lowIndex;
            --highIndex; 
        }
    }
    //recursively sort lower and higher partition
    Quicksort_medianOfThree(numbers,i,highIndex);
    Quicksort_medianOfThree(numbers,highIndex + 1, k);
}

void InsertionSort(int numbers[], int numbersSize) {
    for(int i = 0; i < numbersSize; ++i){ // loop through all of the numbers
        for(int j = i; j < numbersSize; ++j){ // for each of the numbers, compare with sorted portion and swap if lower
            if(numbers[j] < numbers[i]){ // if lower 
                int temp = numbers[j];
                numbers[j] = numbers[i];
                numbers[i] = temp;
            }
        }
    }
}

int main() {
    int arr[NUMBERS_SIZE];
    int arr2[NUMBERS_SIZE];
    int arr3[NUMBERS_SIZE];

    fillArrays(arr, arr2, arr3);

    clock_t Start = clock();
    Quicksort_midpoint(arr, 0, NUMBERS_SIZE);
    clock_t End = clock();
    int elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "Time for Quicksort midpoint in milliseconds: " << elapsedTime << " ms" << endl;
    
    Start = clock();
    InsertionSort(arr2, NUMBERS_SIZE);
    End = clock();
    elapsedTime = (End - Start)/CLOCKS_PER_MS;
    cout << "Time for Insertion Sort in milliseconds: " << elapsedTime << " ms" << endl;

    Start = clock();
    Quicksort_medianOfThree(arr2, 0, NUMBERS_SIZE);
    End = clock();
    elapsedTime = (End - Start)/CLOCKS_PER_MS;
    cout << "Time for Quicksort median of three in milliseconds: " << elapsedTime << " ms" << endl;

}

