#include <iostream> 
#include <forward_list>
#include <list>
#include <vector>
using namespace std;








int main()
{	
	int a[9]={1,2,3,4,5,6,7,8,9};
	forward_list<int> xs(begin(a),end(a));
	cout << any_of(begin(xs),begin(xs),[](int x) { return x==3; });
	cout << any_of(xs.begin(),xs.end(),[](int x) { return x==4; });
	list<int> ys(begin(a),end(a));
	cout << any_of(ys.begin(),ys.end(),[](int x) { return x==5; });
	vector<int> zs(begin(a),end(a));
	cout << any_of(zs.begin(),zs.end(),[](int x) { return x==6; });
	string s("Snoopy");
	cout << any_of(s.begin(),s.end(),[](char c) { return c=='c'; });
}
