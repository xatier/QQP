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

int main() 
{
	{
		cout << "Test 1 ...\n";
		vector<int> v;
		for (int i=1;i<=9;++i) cout << *v.insert(v.cbegin(),i) << ' ';
		cout << endl; 
		cout << v.size() << ' ' << v.capacity() << endl;
		for (int i=0;i<=3;++i) cout << *v.erase(v.cbegin()+i) << ' '; 
		cout << endl;
		cout << v.size() << ' ' << v.capacity() << endl;
	}
	{
		cout << "\nTest 2 ...\n";
		vector<vector<int> > v(2,vector<int>(3,5));
		v[0].pop_back();
		v[1].push_back(6);
		v.push_back(vector<int>(2,7));
		for (vector<vector<int> >::iterator rit=v.begin();rit!=v.end();++rit) { 
			for (vector<int>::iterator cit=rit->begin();cit!=rit->end();++cit) 
				cout << *cit << ' ';
			cout << endl;
		}
	}
	{
		Orz a("Snoopy  "),b("Pluto   "),c("Garfield");
		Orz::debug=true;
		cout << "\nTest 3 ...\n";
		vector<Orz> v{a,c};		// initializer list
		cout << "\nTest 4 ...\n";
		v.insert(v.cbegin()+1,b);
		cout << "\nTest 5 ...\n";
		v.erase(v.cbegin());
		Orz::debug=false;
	}
}
