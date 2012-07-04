/* ----------------------------------------- *
|   QQP homework #5                          |
|   Stack and backtracking                   |
|   Due date:  5/10                          |
|   0016045 ymli @ cs104                     |
* ----------------------------------------- */

#include <iostream>
#include <tuple>
#include "stack5.h"
using namespace std;



int subset (int *a, int n) {
    stack<tuple<int, int> >b;
    stack<int> s(3);
    int sum = 0;
    for (int i = 0; i < n ; i++)
        sum += a[i];

    if (sum % 2 == 1)        // no solution for odd sum
        return 0;

    int i = n, j = sum / 2;
    int ans = 0;             // how many such subset

    while (1) {
        if (i > 1) {
            while (i > 1) {
                b.push(make_tuple(i-1, j));
                s.push(a[i-1]);
                i--;
                j -= a[i];
            }
        }

        if (i == 1) {
            // excluding a[0]
            if (j == 0) {
                // output stack s
                stack<int> t(s);
                while (!t.empty()) {
                    std::cout << t.top() << " ";
                    t.pop();
                }
                std::cout << std::endl;

                ans++;
            }
            // including a[0]
            else if (j == a[0]){
                // output a[0] and stack s 
                std::cout << a[0] << " ";
                stack<int> t(s);
                while (!t.empty()) {
                    std::cout << t.top() << " ";
                    t.pop();
                }
                std::cout << std::endl;

                ans++;
            }
        }

        // backtracking
        if (!b.empty()) {
            i = get<0>(b.top());
            j = get<1>(b.top());
            b.pop();
            s.pop();
        }
        else {
           return ans;
        }
    }
}

int main (void)
{
	int a[9]={1,2,3,4,5,6,7,8,9};
	cout << "Test 1...\n";
	cout << subset(a,7) << " subset(s) in total\n\n";

    cout << "Test 2...\n";
    cout << subset(a,8) << " subset(s) in total\n\n";
	cout << "Test 3...\n";
	cout << subset(a,9) << " subset(s) in total\n\n";

}



		

