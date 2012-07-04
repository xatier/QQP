#include <iostream>
#include "slist.h"
using namespace std;

// Version A
template<class ForwardIterator>
void rotate(ForwardIterator first,ForwardIterator middle,ForwardIterator last)
{

	ForwardIterator next=first;
	while (next!=middle) {
		typename iterator_traits<ForwardIterator>::value_type tmp=*first;
		ForwardIterator it=first,fit=first;
		++fit;
		while (fit!=last) { *it=*fit; ++it; ++fit; }
		*it=tmp;
		++next;
	}
}

// Version B - faster
//template<class ForwardIterator>
//void rotate(ForwardIterator first,ForwardIterator middle,ForwardIterator last)
//{
//	if (first==middle||middle==last) return;
//	ForwardIterator left=first,right=middle,mid=middle;
//	while (true) {
//		typename iterator_traits<ForwardIterator>::value_type tmp=*left;
//		*left=*right;
//		*right=tmp;
//		++left; ++right;
//		if (left==mid) {
//			if (right==last) return; else mid=right; }
//		else 
//			if (right==last) right=mid;
//	}
//}

ostream& operator<<(ostream& os,const list& a)
{
	for (list::const_iterator it=a.begin(); it!=a.end();++it) 
		os << *it << ' ';
	return os << endl;
}

int main()
{
	list a; 
	for (int i=1;i<=7;i++) a.push_back(i);
	list b(a),c(a);
	::rotate(a.begin(),a.begin(),a.end());
	cout << a;
	::rotate(a.begin(),a.end(),a.end());
	cout << a;
	::rotate(a.begin(),++++++a.begin(),a.end());
	cout << a;
	list::iterator b_middle=b.insert(b.end(),8);
	::rotate(b.begin(),b_middle,b.end());
	cout << b;
	list::iterator c_middle=c.insert(c.end(),8);
	c.insert(c.end(),9);
	::rotate(c.begin(),c_middle,c.end());
	cout << c;
}