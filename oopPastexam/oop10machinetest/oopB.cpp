#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

// Version 1: stack<char>
//void out(stack<char>& t) 
//{
//	if (!t.empty()) {
//		char c=t.top();	
//		t.pop(); out(t); cout << c; t.push(c);
//	}
//}
//
//int substring(int i,const string& s,stack<char>& t)
//{
//	if (i==s.size()) {
//		out(t);
//		cout << endl;
//		return 1;
//	} else {
//		int x=substring(i+1,s,t);
//		t.push(s[i]);
//		int y=substring(i+1,s,t);
//		t.pop();
//		return x+y;
//	}
//}
//
//int substring(const string& s)
//{
//	stack<char> t;
//	return substring(0,s,t);
//}

// Version 2: vector<char>
//int substring(int i,const string& s,vector<char>& t)
//{
//	if (i==s.size()) {
//		for (vector<char>::iterator it=t.begin(); it!=t.end();++it) cout << *it;
//		cout << endl;
//		return 1;
//	} else {
//		int x=substring(i+1,s,t);
//		t.push_back(s[i]);	// or, t.insert(t.end(),s[i]);
//		int y=substring(i+1,s,t);
//		t.pop_back();       // or, t.erase(t.end()-1);
//		return x+y;
//	}
//}
//
//int substring(const string& s)
//{
//	vector<char> t;
//	return substring(0,s,t);
//}

// Version 3: string
int substring(int i,const string& s,string& t)
{
	if (i==s.size()) {
		cout << t;
		cout << endl;
		return 1;
	} else {
		int x=substring(i+1,s,t);
		t.insert(t.end(),s[i]);
		int y=substring(i+1,s,t);
		t.erase(t.end()-1);
		return x+y;
	}
}

int substring(const string& s)
{
	string t;
	return substring(0,s,t);
}

// Version 4: remove duplication
//int substring(int i,const string& s,string& t,vector<string>& v)
//{
//	if (i==s.size()) {
//		if (binary_search(v.begin(),v.end(),t)) return 0;
//		//v.insert(lower_bound(v.begin(),v.end(),t),t);
//		v.push_back(t); sort(v.begin(),v.end());
//		cout << t;
//		cout << endl;
//		return 1;
//	} else {
//		int x=substring(i+1,s,t,v);
//		t.insert(t.end(),s[i]);
//		int y=substring(i+1,s,t,v);
//		t.erase(t.end()-1);
//		return x+y;
//	}
//}
//
//int substring(const string& s)
//{
//	string t;
//	vector<string> v;
//	return substring(0,s,t,v);
//}

int main()
{
	cout << "Test 1 ...\n";
	string a("cafe");
	cout << substring(a) << " substrings\n";
	cout << "\nTest 2 ...\n";
	string b("sees");
	cout << substring(b) << " substrings\n";
}
