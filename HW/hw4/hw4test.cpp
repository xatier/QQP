#include <iostream>
#include <vector>
using namespace std;








template<typename T>
void test_lcs(const T* x,int m,const T* y,int n) 
{
	cout << "Sequence X: ";
	for (int i=0;i<m;i++) cout << x[i] << ' '; cout << endl;
	cout << "Sequence Y: ";
	for (int i=0;i<n;i++) cout << y[i] << ' '; cout << endl;
	cout << "Version A: Vector\n";
	cout << "Length of lcs = " << A::lcs(x,m,y,n) << endl;
	cout << "Version B: new and delete\n";
	cout << "Length of lcs = " << B::lcs(x,m,y,n) << endl;
	cout << endl;
}

int main()
{
	int x[6]={2,5,3,1,6,4},y[6]={1,2,3,4,5,6}; test_lcs(x,6,y,6); 
	test_lcs("pioneer",7,"springbreak",11);
	const char* a[6]={"Snoopy","Pluto","Garfield","Shrek","Micky","Lorax"};
	const char* b[7]={"Garfield","Doraamon","Snoopy","Micky","Pluto","Shrek","Lorax"};
	test_lcs(a,6,b,7);
}