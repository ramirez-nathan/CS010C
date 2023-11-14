#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Node {
    string payload;
    Node* next;
};

Node* newNode(string payload) {
    
    // allocate memory for new node
    Node *t = new Node();
    
    //returns a pointer to the object with payload value of intialized payload
    t->payload = payload;
    t->next = nullptr;
    return t;
}

Node* loadGame(int n, vector<string> names) {
    Node* head = nullptr;
    Node* prev = nullptr;
    string name;

    //iterate through the laop creates a new node for each name
    for (int i = 0; i < n; ++i) {
        name = names.at(i);
        //if first node is target then intialize head and prev to the same node
        if (head == nullptr) {
            head = newNode(name);
            prev = head;
        } 
        //else create a new node and set next pointer of the prev node to the new node
        else {
            prev->next = newNode(name);
            prev = prev->next;
            
        }
    }

    //make the linked list circular
    if (prev != nullptr) {
       prev->next = head;
    }

    //return pointer of the head of the linked list
    return head;
}

void print(Node* start) { // prints list
    Node* curr = start;
    while (curr != nullptr) {
        cout << curr->payload << endl;
        curr = curr->next;
        //if next node is the start, exit the loop
        if (curr == start) {
            break; 
        }
    }
}

Node* runGame(Node* start, int k) { // josephus w circular list, k = num skips
    Node* curr = start;
    Node* prev = curr;

    //loop until the last person
    while (curr->next != nullptr && curr->next != curr) { 
        //loop until the kth node
        for (int i = 0; i < k; ++i) { 
          prev = curr;
          curr = curr->next;
        }
        //remove kth node
        prev->next = curr->next;
        delete curr;
        curr = prev->next;
    }

    return curr; // last person standing
}

/* Driver program to test above functions */
int main() {
    int n=1, k=1; // n = num names; k = num skips (minus 1)
    string name;
    vector<string> names;

    // get inputs
    cin >> n >> k;
    while (cin >> name && name != ".") { names.push_back(name); } // EOF or . ends input

    // initialize and run game
    Node* startPerson = loadGame(n, names);
    Node* lastPerson = runGame(startPerson, k);

    if (lastPerson != nullptr) {
        cout << lastPerson->payload << " wins!" << endl;
    } else {
        cout << "error: null game" << endl;
    }

    return 0;
}