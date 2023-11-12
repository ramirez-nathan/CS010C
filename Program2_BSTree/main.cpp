#include <iostream>
#include <limits>
#include "BSTree.h"
// #include "test_bst.h"

using namespace std;

void printOrders(BSTree *tree) {
  cout << "Preorder = ";
  tree->preOrder( );
  cout << endl;
  
  cout << "Inorder = ";
  tree->inOrder( );
  cout << endl; 
  
  cout << "Postorder = ";
  tree->postOrder( );
  cout << endl;
}

int menu() {
  int choice = 0;
  cout << endl << "Enter menu choice: ";
  cout << endl;
  cout 
    << "1. Insert" << endl
    << "2. Remove" << endl
    << "3. Print" << endl
    << "4. Search" << endl
    << "5. Smallest" << endl
    << "6. Largest" << endl
    << "7. Height" << endl
    << "8. Quit" << endl;
  cin >> choice;

  // fix buffer just in case non-numeric choice entered
  // also gets rid of newline character
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  return choice;
}

int main( ) {
    // Pass all your tests before running the executable main
    // run_tests();  // TODO: Remove before submitting
    // return 0;

    BSTree tree;

    int choice = menu();

    string entry;

    while (choice != 8) {

        if (choice == 1) {
            cout << "Enter string to insert: ";
            cout << endl;
            getline(cin, entry);
            tree.insert(entry);
        } 
        else if (choice == 2) {
            cout << "Enter string to remove: ";
            getline(cin, entry);
            cout << endl;
            tree.remove(entry);
        } 
        else if (choice == 3) {
            printOrders(&tree);
        } 
        else if (choice == 4) {
            cout << "Enter string to search for: ";
            getline(cin, entry);
            cout << endl;
            if(tree.search(entry) == false){
                cout << "Not Found" << endl;
            }
            else{
                cout << "Found" << endl;
            }
        } 
        else if (choice == 5) {
            cout << "Smallest: " << tree.smallest() << endl;
        } 
        else if (choice == 6) {
            cout << "Largest: " << tree.largest() << endl;
        } 
        else if (choice == 7) {
            cout << "Enter string: ";
            getline(cin, entry);
            cout << endl;
            if(tree.height(entry) == -1){
                cout << "Height of subtree rooted at " << entry << ": " << tree.height(entry) << endl;
            }
            else{
                cout << "Height of subtree rooted at " << entry << ": " << tree.height(entry) << endl;
            }
        }
        else{
            break;
        }
        //fix buffer just in case non-numeric choice entered
        choice = menu();
    }
    return 0;
}