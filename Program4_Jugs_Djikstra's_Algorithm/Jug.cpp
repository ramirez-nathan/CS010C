#include "Jug.h"
#include <algorithm>

using namespace std;

Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA) 
        : Ca(Ca), Cb(Cb), N(N), cfA(cfA), cfB(cfB), ceA(ceA), ceB(ceB), cpAB(cpAB), cpBA(cpBA) {}

Jug::~Jug() {}

bool Jug::isTarget(int a, int b) const {
    return (a == 0 && b == N);
}

void Jug::priorityEnqueue(priority_queue<State>& pq, int a, int b, int c, const string& s) {
    if (a >= 0 && b >=0 && a <= Ca && b <= Cb) { // checks if water in A & B is non negative & capacity per jug is not exceeded
		string state = to_string(a) + "," + to_string(b); // creates a key for the new state

		if (find(visited.begin(), visited.end(), state) == visited.end()) { // checks if the state key has not been visited before
			visited.push_back(state); // pushes the state key string into visited vector
			pq.push(State(a, b, c, s)); // pushes the new state onto priority queue
		}
	}
}

int Jug::solve(string& solution) {
    // impossible cases
    solution = "";

    if (N > Ca + Cb) return -1; // if target is greater than both jugs combined

    if (N > Cb) return -1; // if target is greater than capacity of Jug B

    if (Ca == 0 && Cb != N) return -1; // if Jug A's capacity is 0 and Jug B's capacity is not the target

    if (Cb == 0 && Ca != N) return -1; // if Jug B's capacity is 0 and Jug A's capacity is not the target

    if (Ca < 0 || Cb < 0 || N < 0 || ceB < 0 || cfA < 0 || cfB < 0 || ceA < 0 || ceB < 0 || cpAB < 0 || cpBA < 0 ) return -1; // if any input is negative

    if (Ca > 1000 || Cb > 1000) return -1; // if capacities are too high

    // Djikstra's Algorithm
    priority_queue<State> pq;
    visited.clear();

    pq.push(State(0, 0 , 0, ""));
    visited.push_back("0,0");

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        int a = current.A;
        int b = current.B;
        int cost = current.cost;
        string steps = current.steps;

        if (isTarget(a, b)) {
            solution = steps + "success " + to_string(cost);
            return 1;
        }

        // Fill A
		priorityEnqueue(pq, Ca, b, cost + cfA, steps + "fill A\n");

		// Fill B
		priorityEnqueue(pq, a, Cb, cost + cfB, steps + "fill B\n");

		// Empty A
		priorityEnqueue(pq, 0, b, cost + ceA, steps + "empty A\n");

		// Empty B
		priorityEnqueue(pq, a, 0, cost + ceB, steps + "empty B\n");

		// Pour A to B
		int pourAB = min(a, Cb - b);
		priorityEnqueue(pq, a - pourAB, b + pourAB, cost + cpAB, steps + "pour A B\n");

		// Pour B to A
		int pourBA = min(b, Ca - a);
		priorityEnqueue(pq, a + pourBA, b - pourBA, cost + cpBA, steps + "pour B A\n");
    }

    solution = ""; // No solution
    return 0;
}