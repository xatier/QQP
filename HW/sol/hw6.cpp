#include <iostream>
#include <numeric>
#include "stack6.h"
using namespace std;   

int subset(int* a,int i,int j,stack<int> s)
{
	if (i==0) 
		if (j==0||j==a[0]) {
			if (j==a[0]) cout << a[0] << ' ';
			stack<int> t(s);
			while (!t.empty()) {
				cout << t.top() << ' '; t.pop();
			}			
			cout << endl;
			return 1;
		} else return 0;
	else {
		s.push(a[i]);
		int c=subset(a,i-1,j-a[i],s);
		s.pop();
		return c+subset(a,i-1,j,std::move(s));
	}
}

int subset(int* a,int n)
{
	int b=accumulate(a,a+n,0,[](int x,int y){return x+y;});
	if (b%2==1) return 0;
	return subset(a,n-1,b/2,stack<int>());
}

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
	stack<o_O> s;
	o_O oO;
	s.push(oO);
	s.push(std::move(oO));
}

