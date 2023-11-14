#include <iostream>
#include "arithmeticExpression.h"
#include <fstream>
#include <sstream>
#include <stack>

using namespace std;

void arithmeticExpression::buildTree() {
    string postfixString = infix_to_postfix(); // convert infix to postfix
    stack<Node*> s;
    for (const auto& c:postfixString) { // iterate for each char in the string
        if (isalpha(c)) { // if current char is an alphabet push it on the stack
            s.push(new Node(c, 0));
        }
        else {
            Node* expr = new Node(c, 0);
            
            // create a temporary node to store expression node's right for the top thing in the stack
            Node* right = s.top();
            s.pop(); // pop to be able to get second highest thing on the stack
            Node* left = s.top();
            s.pop();
            // set expr's right and left to their nodes and push onto the stack as one
            expr->right = right;
            expr->left = left;
            s.push(expr);
        }
    }
    root = s.top();
}

void arithmeticExpression::infix(){
    infix(root); // calling private recursive helper
}

void arithmeticExpression::infix(Node *root){
    if(root != nullptr){
        if(root->left != nullptr){ // if curr is first thing that needs to be printed then parenthesis
            cout << "(";
        }
        infix(root->left); 
        cout << root->data;
        infix(root->right); 
        if(root->right != nullptr){ // if curr is last thing that needs to be printed then parenthesis
            cout << ")";
        }
    }
}

void arithmeticExpression::postfix() {
    postfix(root); // calls recursive helper function
}

void arithmeticExpression::postfix(Node* root) {
    if (root != nullptr) { // edge case if tree is empty
        // prints after traversing to the right, left then curr of each subtree
        postfix(root->left);
        postfix(root->right);
        cout << root->data;
    }
}

void arithmeticExpression::prefix(){
    prefix(root); // calling private recursive helper
}

void arithmeticExpression::prefix(Node *root){
    if(root != nullptr){ // edge case to make sure not printing empty trees
    // prints the very left first then goes to the right of each left subtree after
        cout << root->data;
        prefix(root->left); 
        prefix(root->right); 
    }
}

int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}


/* void arithmeticExpression::visualizeTree(const string& outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
} */


