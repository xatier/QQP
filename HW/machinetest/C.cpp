#include <iostream>
#include <string>
#include "deque6.h"
using namespace std;   

int main()
{
	deque<int> d{1,2,3,4,5,6,7,8,9};
	d.remove_if([](int x) { return x%2==0; });
	cout << d << endl;
	deque<string> e{"Snoopy","Pluto","Garfield","Shrek","Doraamon","Pluto"};
	e.remove_if([](const string& s) { return s[0]=='S'; });
	cout << e << endl;
	e.remove_if([&](const string& s) { return s==e.back(); });
	cout << e << endl;
}
