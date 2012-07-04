#include <iostream>
#include "list8.h"
using namespace std;

template<typename T>
ostream& operator<<(ostream& os,const list<T>& v)
{
	typename list<T>::const_iterator it;
	for (it=v.begin();it!=v.end();++it)
		os << *it << ' ';
	return os << endl;
}

int main()
{
	{
		cout << "Testing part D1 ...\n";
		int a[9]={1,2,3,4,5,6,7,8,9};
		list<int> b(a,a+9);
		list<int> c(a,a+5);
		list<int> d(a+5,a+9);
		b.splice(b.begin(),c);
		cout << "List b: " << b;
		cout << "List c: " << c;
		b.splice(b.end(),d);
		cout << "List b: " << b << endl;
	}
	{
		cout << "Testing part D2 ...\n";
		char a[]="s@n#o!o$p%y";
		list<char> b(a,a+sizeof(a)-1);
		list<int> c(b);
		cout << b << c;
		list<char> d(c);
		cout << d << c;
	}





}