#ifndef JUG_H
#define JUG_H
#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

class Jug {
    public:
        Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA);
        ~Jug();

        //solve is used to check input and find the solution if one exists
        //returns -1 if invalid inputs. solution set to empty string.
        //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
        //returns 1 if solution is found and stores solution steps in solution string.
        int solve(string& solution); // reference b/c string will be modified
    private:
                        // LETS TAKE A PRIORITY QUEUE APPROACH TO THE GRAPH    
        // priv struct State --> contains the different states of jugs 
        struct State {
            int A, B, cost;
            string steps;

            // Constructor
            State(int a, int b, int c, const string& s) : A(a), B(b), cost(c), steps(s) {}

            // need to define overload operator< for priority queue (some stl priority queue .push silly behavior) since we will be push()'ing
            bool operator<(const State& other) const {
                return cost > other.cost; // Inversed for the min-heap
            }
        };

        vector<string> visited; // vector of visited state keys
        int Ca, Cb, N, cfA, cfB, ceA, ceB, cpAB, cpBA;
        
        // Checks if goal state has been reached
        bool isTarget(int a, int b) const;

        // Enqueues a new state to priority queue
        void priorityEnqueue(priority_queue<State>& pq, int a, int b, int c, const string& s);
};





#endif  
