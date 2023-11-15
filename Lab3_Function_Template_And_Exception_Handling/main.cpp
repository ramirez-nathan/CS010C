#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

vector<char> createVector();

template<typename T>
unsigned min_index(const vector<T> &vals, unsigned index) { // passes in an index of type int and a vector of type T (T could be string, double or int)
    unsigned minIndex = index;
    //iterate through the vector starting at index from parameter
    for (unsigned int i = index; i < vals.size(); ++i) {
        if (vals.at(i) < vals.at(minIndex)) {
            minIndex = i;
        }
    }
    return minIndex;
}

template<typename T>
void selection_sort(vector <T> &vals) { // passes in a vector of type T and sorts them based on the selection sort method
    unsigned int smallestIndex = 0;
    T placeholder;
    //iterate until end of the vector
    for (unsigned int i = 0; i < vals.size(); ++i) {
        // find the smallest value
        smallestIndex = min_index(vals, i);
        // if smallestIndex is smaller than the current value in the index of i
        if (vals.at(smallestIndex) < vals.at(i)) {
            //swap smallest value with i
            placeholder = vals.at(i);
            vals.at(i) = vals.at(smallestIndex);
            vals.at(smallestIndex) = placeholder;
        }

    }
}

template<typename T>
T getElement(const vector<T> &vals, const int &index) { // passes in a vector of type T and an index of type int
    //if the index is out of range throw an exception
    if((index + 1) > static_cast<const int>(vals.size())) {
        throw out_of_range("not in range");
    }

    return vals.at(index);
}

vector<char> createVector() {
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    //loop pushing back a list of random values
    for(int i = 0; i < vecSize; i++) {
        vals.push_back(c);
        c++;
    }
    return vals;
}


int main(){
    //unsigned int num;
    //test harness for vector of strings selection sort and min_index
    vector<string> stringVals = {"asd", "cas", "as", "sdf"};

    cout << "testing string selection sort" << endl;

    // loop for outputting string values before
    for (unsigned int i = 0; i < stringVals.size(); ++i) {
        cout << stringVals.at(i) << " ";
    }
    cout << endl;

    selection_sort(stringVals);

    // loop for outputting string values after sorting
    for (unsigned int i = 0; i < stringVals.size(); ++i) {
        cout << stringVals.at(i) << " ";
    }
    cout << endl;

    // test harness for vector of ints selection sort and min_index
    vector<int> intVals = {1, 4, 2, 0};

    // loop for outputting int values before 
    for (unsigned int i = 0; i < intVals.size(); ++i) {
        cout << intVals.at(i) << " ";
    }
    cout << endl;

    selection_sort(intVals);

    // loop for outputting int values after sorting
    for (unsigned int i = 0; i < intVals.size(); ++i) {
        cout << intVals.at(i) << " ";
    }
    cout << endl;

    //test harness for getElement function
    srand(time(0));
    vector<char> vals = createVector();
    char curChar;
    int index;
    int numOfRuns = 10;
    while(--numOfRuns >= 0) {
        cout << "Enter a number: " << endl;
        cin >> index;
        try {
            curChar = getElement(vals, index);
        }
        catch (const out_of_range& except) {
            cout << "out of range exception occured" << endl;
        }

        cout << "Element located at " << index << ": is " << curChar << endl;
    }
    return 0;
}
