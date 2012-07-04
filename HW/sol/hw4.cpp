#include <iostream>
#include <vector>
using namespace std;


namespace A {
	template<typename T>
	void lcs (const T* x,int i,const T* y,int j,
					const vector<vector<int> >& tbl)
	{
		int k=0;
		for(int a=0;a<=i;a++) {
			for(int b=j;b>=1;b--) {
				if(tbl[a][b]>tbl[a][b-1]&& tbl[a][b]>k) {
					cout << x[a-1] << " ";
					k=tbl[a][b];
					break;
				}
			}
		}

	}

	template<typename T>
	int lcs (const T* x,int i,const T* y,int j,
						vector<vector<int> >& tbl)
	{
		if(tbl[i][j]==0) {
			if(i==0 || j==0) tbl[i][j]=0;
			else if(x[i-1]==y[j-1])
				tbl[i][j]=lcs(x,i-1,y,j-1,tbl)+1;
			else {
				if((lcs(x,i,y,j-1,tbl))>=(lcs(x,i-1,y,j,tbl)))
					tbl[i][j]=tbl[i][j-1];
				else
					tbl[i][j]=tbl[i-1][j];
			}
		}
		return tbl[i][j];
	}

	template<typename T>
	int lcs (const T* x,int m,const T* y,int n)
	{
		vector<vector<int> > tbl(m+1,vector<int>(n+1,0));
		int ans=lcs (x,m,y,n,tbl);
		cout << "Lcs :";
		lcs (x,m,y,n,const_cast<const vector<vector<int> > >(tbl));
		cout << endl;
		return ans;
	}

}


namespace B {
	template<typename T>
	void lcs (const T* x,int i,const T* y,int j,
							const int*const* tbl)
	{

		int k=0;
		for(int a=0;a<=i;a++) {
			for(int b=j;b>=1;b--) {
				if(tbl[a][b]>tbl[a][b-1]&& tbl[a][b]>k) {
					cout << x[a-1] << " ";
					k=tbl[a][b];
					break;
				}
			}
		}
	}


	template<typename T>
	int lcs (const T* x,int m,const T* y,int n)
	{
		int** tbl=new int*[m+1];
		for(int i=0;i<=m;i++) tbl[i]=new int[n+1];
		for(int j=0;j<=n;j++) tbl[0][j]=0;
		for(int i=0;i<=m;i++) tbl[i][0]=0;
		for(int i=1;i<=m;i++) {
			for(int j=1;j<=n;j++) {
				if(x[i-1]==y[j-1]) tbl[i][j]=tbl[i-1][j-1]+1;
				else
					tbl[i][j]= tbl[i][j-1]>=tbl[i-1][j]? tbl[i][j-1]:tbl[i-1][j];
			}
		}
		int ans=tbl[m][n];
		cout << "Lcs: ";
		lcs(x,m,y,n,tbl);
		cout <<endl;
		for(int i=m;i>=0;i--) delete [] tbl[i];
		return ans;
	}
}







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
	system("pause");
}
