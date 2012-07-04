/* ----------------------------------------- *
|   QQP homework #6                          |
|   Deque, stack, and set partition          |
|   Due date:  5/10                          |
|   0016045 ymli @ cs104                     |
* ----------------------------------------- */

#include <iostream>
#include <numeric>
#include "stack6.h"
using namespace std;   

// recursively calculate the answer
int rec (int *a, int i, int j) {
    // stack (in the heap)
    static stack<int> s;

    // t[i, j] = t[i-1, j-a[i-1]] + t[i-1, j] for i > 1
    if (i > 1) {
        s.push(a[i-1]);
        int aa = rec(a, i-1, j-a[i-1]);
        s.pop();
        return aa + rec(a, i-1, j);
    }

    if (i == 1) {
        if (j == 0) {
            // excluded a[0]
            stack<int> t(s);
            while (!t.empty()) {
                std::cout << t.top() << " ";
                t.pop();
            }
            std::cout << std::endl;
            return 1;
        }
        else if (j == a[0]) {
            // included a[0]
            std::cout << a[0] << " ";
            stack<int> t(s);
            while (!t.empty()) {
                std::cout << t.top() << " ";
                t.pop();
            }
            std::cout << std::endl;
            return 1;
        }
        // otherwise
        else {
            return 0;
        }
    }
    else {
        return 0;
    }
}

int subset (int *a, int n) {
    // sum of elements in the array
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += a[i];

    // no such solution
    if (sum % 2 == 1)
        return 0;

    return rec(a, n, sum/2);
}


// o_O
struct o_O {
	o_O() {}
	o_O(const o_O&) { cout << "o_O copied\n"; }
	o_O(o_O&&) { cout << "o_O moved\n"; }
};

int main()
{


	int a[9]={1,2,3,4,5,6,7,8,9};
	cout << "Test 1...\n";
	cout << subset(a,7) << " subset(s) in total\n\n";
	cout << "Test 2...\n";
	cout << subset(a,8) << " subset(s) in total\n\n";
	cout << "Test 3...\n";
	cout << subset(a,9) << " subset(s) in total\n\n";
	cout << "Test 4...\n";

	deque<o_O> s;
	o_O oO;
	s.push_back(oO);
	s.push_back(std::move(oO));

}

