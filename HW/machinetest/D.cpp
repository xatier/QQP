#include <iostream>
#include <string>
#include "vector7.h"
using namespace std;

struct Orz {
	Orz(const char* s="") : s(s) { if (debug) cout << s << " constructed\n"; }
	Orz(const Orz& rhs) : s(rhs.s) { if (debug) cout << s << " copy-constructed\n"; }
	Orz(Orz&& rhs) : s(std::move(rhs.s)) { if (debug) cout << s << " move-constructed\n"; }
	Orz& operator=(const Orz& rhs) 
	{ 
		if (debug) cout << rhs.s << " copy-assigned to " << s << endl; 
		s=rhs.s; 
		return *this; 
	}
	Orz& operator=(Orz&& rhs) 
	{ 
		if (debug) cout << rhs.s << " move-assigned to " << s << endl; 
		s=std::move(rhs.s); 
		return *this; 
	}
	~Orz() { if (debug) cout << s << " destructed\n"; }
	string s;
	static bool debug;
};
bool Orz::debug=false;

bool operator==(const Orz& lhs,const Orz& rhs) { return lhs.s==rhs.s; }
ostream& operator<<(ostream& os,const Orz& rhs) { return os << rhs.s; }

void test1()
{
	cout << "Test 1 ...\n";
	vector<string> u{"Snoopy","Pluto","Garfield"};
	vector<string> v(u.begin(),u.end());
	cout << v.capacity() << ' '; for (const string& s: v) cout << s << ' '; cout << endl;
	vector<string> w(make_move_iterator(u.begin()),make_move_iterator(u.end()));
	cout << w.capacity() << ' '; for (const string& s: w) cout << s << ' '; cout << endl;
	cout << u.size() << ' '; for (const string& s: u) cout << s << ' '; cout << endl;
}

void test2()
{
	cout << "\nTest 2 ...\n";
	Orz a("Snoopy  "),b("Pluto   "),c("Garfield");
	vector<Orz> v{a,c,b,c,c,a,b,c,c};
	Orz::debug=true;
	v.remove_if([&](const Orz& s) { return s==c; });
	for (const Orz& x : v) cout << x; cout << endl;
	Orz::debug=false;
}

void test3()
{
	cout << "\nTest 3 ...\n";
	vector<vector<int> > v{{2,3,4,5},{2,2},{5,6},{2,7,2},{2},{8,2,9,2}};
	for (vector<int>& w : v) 
		w.remove_if([](int x) { return x==2; });
	v.remove_if([](const vector<int>& w) { return w.size()==0; });
	for (const vector<int>& w : v) {
		for (int x : w) cout << x;
		cout << endl;
	}
}

int main()
{
	test1(); test2(); test3();        
}
