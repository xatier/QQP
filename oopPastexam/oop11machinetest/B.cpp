#include <iostream>
#include <functional>
#include <numeric>
#include <vector>
using namespace std;   

//Version A
int subset(int* a,int n)
{
	int b=accumulate(a,a+n,0,plus<int>());
	if (b%2==1) return 0;
	vector<vector<int> > t(n,vector<int>(1+b/2));
	t[0][0]=t[0][a[0]]=1;
	for (int i=1;i<n;i++)
		for (int j=0;j<1+b/2;j++) 
			t[i][j] = j>=a[i]? t[i-1][j]+t[i-1][j-a[i]]: t[i-1][j];
	return t[n-1][b/2];
}

//Version B (Bonus)
//void show(vector<vector<int> >& s,int i,int j)
//{
//	if (i==0) {
//		if (s[i][j]>0) cout << j << ' ';  // j==a[0]
//	} else 
//		if (s[i][j]==0) show(s,i-1,j);
//		else { 
//			show(s,i-1,j-s[i][j]); cout << s[i][j] << ' ';
//		}
//}
//
//int subset(int* a,int n)
//{
//	int b=accumulate(a,a+n,0,plus<int>());
//	if (b%2==1) return 0;
//	vector<vector<int> > t(n,vector<int>(1+b/2)),s(n,vector<int>(1+b/2,-1));
//	t[0][0]=t[0][a[0]]=1;
//	s[0][0]=0; s[0][a[0]]=a[0];
//	for (int i=1;i<n;i++)
//		for (int j=0;j<1+b/2;j++) {
//			if (t[i-1][j]>0) s[i][j]=0;
//			else if (j>=a[i]&&t[i-1][j-a[i]]>0) s[i][j]=a[i];
//			t[i][j] = j>=a[i]? t[i-1][j]+t[i-1][j-a[i]]: t[i-1][j];
//		}
//	if (t[n-1][b/2]>0) { cout << "One subset: "; show(s,n-1,b/2); cout << endl; }
//	return t[n-1][b/2];
//}

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