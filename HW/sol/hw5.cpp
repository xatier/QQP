#include <iostream>
#include <numeric>
#include <tuple>
#include "stack5.h"
using namespace std;

int subset(int* a,int i,int j)
{
	stack<tuple<int,int> > b;
	stack<int> s(3);
	int c=0; 
	do {
		while (i>0&&j>=0) {
			b.push(make_tuple(i-1,j));
			s.push(a[i]); j-=a[i]; i--; 
		}
		if (j==0 || j==a[0]) {
			c+=1;
			if (j==a[0]) cout << a[0] << ' ';
			stack<int> t(s);
			while (!t.empty()) {
				cout << t.top() << ' '; t.pop();
			}
			cout << endl;
		}
		if (!b.empty()) { 
			i=get<0>(b.top()); j=get<1>(b.top()); b.pop(); s.pop();
		}
		else return c;
	} while (true);
}

int subset(int* a,int n)
{
	int b=accumulate(a,a+n,0,[](int x,int y){return x+y;});
	if (b%2==1) return 0;
	return subset(a,n-1,b/2);
}

int main()
{
	int a[9]={1,2,3,4,5,6,7,8,9};
	cout << "Test 1...\n";
	cout << subset(a,7) << " subset(s) in total\n\n";
	cout << "Test 2...\n";
	cout << subset(a,8) << " subset(s) in total\n\n";
	cout << "Test 3...\n";
	cout << subset(a,9) << " subset(s) in total\n\n";
}



		

