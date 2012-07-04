/* ----------------------------------------- *
|   QQP homework #4                          |
|   Longest Common Subsequence               |
|   Due date:  4/12                          |
|   0016045 ymli @ cs104                     |
* ----------------------------------------- */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


namespace A {
    template<typename T>
    void lcs(const T* x,int i,const T* y,int j,
                const vector<vector<int> >& tbl) {

        if (i > 0 && j > 0) {
            if (x[i-1] == y[j-1]) {
                lcs(x, i-1, y, j-1, tbl);
                cout << x[i-1] << " ";
            }
            else {
                if (tbl[i][j-1] > tbl[i-1][j])
                    lcs(x, i, y, j-1, tbl);
                else
                    lcs(x, i-1, y, j, tbl);
            }
        }
    }

    template<typename T>
    int lcs(const T* x,int i,const T* y,int j,
                vector<vector<int> >& tbl){
        if (tbl[i][j] == 0) {
            if (i == 0 || j == 0)
                tbl[i][j] = 0;
            else if (i > 0 && j > 0) {
                if (x[i-1] == y[j-1])
                    tbl[i][j] = lcs(x, i-1, y, j-1, tbl) + 1;
                else
                    tbl[i][j] = max(lcs(x, i, y, j-1, tbl), lcs(x, i-1, y, j, tbl));
            }
        }
        return tbl[i][j];
    }

    template<typename T>
    int lcs(const T* x,int m,const T* y,int n) {
        vector<vector<int> > tbl(m+1, vector<int>(n+1, 0));
        int ans = lcs(x, m, y, n, tbl);
        cout << "Lcs: ";
        lcs(x, m, y, n, vector<vector<int> >(tbl));
        cout << endl;
        return ans;
    }
}

namespace B {
    template<typename T>
    void lcs(const T* x,int i,const T* y,int j,
                const int*const* tbl) {
        if (i > 0 && j > 0) {
            if (x[i-1] == y[j-1]) {
                lcs(x, i-1, y, j-1, tbl);
                cout << x[i-1] << " ";
            }
            else {
                if (tbl[i][j-1] > tbl[i-1][j])
                    lcs(x, i, y, j-1, tbl);
                else
                    lcs(x, i-1, y, j, tbl);
            }
        }
    }

    template<typename T>
    int lcs(const T* x,int m,const T* y,int n) {
        int **c = NULL;
        c = new int *[m+1];
        for (int i = 0; i <= m; i++)
            c[i] = new int [n+1];
            
        int **tbl = NULL;
        tbl = new int *[m+1];

        for (int i = 0; i <= m; i++)
            tbl[i] = new int [n+1];

        for (int i = 0; i <= m; i++)
            c[i][0] = 0;

        for (int j = 0; j <= n; j++)
            c[0][j] = 0;

        for (int i = 0; i <= m; i++)
            for (int j = 0; j <= n; j++)
                if (i > 0 && j > 0) {
                    if (x[i-1] == y[j-1])
                        c[i][j] = c[i-1][j-1] + 1;
                    else
                        c[i][j] = max(c[i][j-1], c[i-1][j]);
                }

        for (int i = 0; i <= m; i++)
            for (int j = 0; j <= n; j++)
                tbl[i][j] = c[i][j];

        cout << "Lcs: ";
        lcs (x, m, y, n, tbl);
        cout << endl;

        int ans = c[m][n];
        for (int i = 0; i <= m; i++)
            delete [] c[i];
        delete [] c;

        for (int i = 0; i <= m; i++)
            delete [] tbl[i];
        delete [] tbl;

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
}
