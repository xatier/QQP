#include <iostream>
#include <string>
#include "vector7.h"
using namespace std;

class str {
	friend ostream& operator<<(ostream&,const str&);
public:
	str(const char* s="doraemon") : s(s) { if (msg) cout << s << " constructed" << endl; }
	str(const str& rhs) : s(rhs.s) { if (msg) cout << s << " copy-constructed" << endl; }
	str& operator=(const str& rhs) 
	{ 
		if (this!=&rhs) { 
			if (msg) cout << rhs.s << " copy-assigned-to " << s << endl; 
			s=rhs.s; 
		}  
		return *this; 
	}
	~str() { if (msg) cout << s << " destructed"<< endl; }
	static bool msg;
private:
	string s;
};
bool str::msg=false;

ostream& operator<<(ostream& os,const str& s) { return os << s.s; }

template<typename T>
ostream& operator<<(ostream& os,const vector<T>& v)
{
	typename vector<T>::const_iterator it;
	for (it=v.begin();it!=v.end();++it)
		os << *it << ' ';
	return os << endl;
}

int main() 
{
	vector<int> v,w;
	for (int i=1;i<=3;i++) v.push_back(i);
	v.pop_back();
	for (int i=1;i<=5;i++) w.push_back(i);
	cout << "Test 1...\n";
	v+=v; cout << v; cout << v.capacity() << endl;
	v+=w; cout << v; cout << v.capacity() << endl;
	v+=w; cout << v; cout << v.capacity() << endl;
	v+=v; cout << v; cout << v.capacity() << endl;
	cout << "\nTest 2...\n";
	vector<str> s,t;
	str::msg=false;
	s.push_back("doraemon");
	s.push_back("garfield");
	s.push_back("lionking"); s.pop_back();
	t.push_back("mermaids");
	str::msg=true;
	s+=t;
	cout << "\nTest 3...\n";
	s+=s;
	str::msg=false;
}

