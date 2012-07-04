/* ----------------------------------------- *
|   QQP homework #2                          |
|   Maximum Contiguous Subsequence           |
|   Due date:  3/29                          |
|   0016045 ymli @ cs104                     |
* ----------------------------------------- */

#include <iostream>
#include <limits>
#include <tuple>
#include <algorithm>
#include <cstdio>
using namespace std;


template<typename T>
pair<int, int> mcs(T* a, int n, T& maxsum);

template<typename T, int n>
pair<int, int> mcs(T (&a)[n],T& maxsum);

template<typename T>
tuple<T, int, int> find_pair_mid(T *a, int l, int h) {
    int m = (l+h) / 2;
    T sum, max;
    sum = max = T(0);
    int left = m;
    for (int i = m; i >= l; i--) {
        sum += a[i];
        if (sum > max) {
            max = sum;
            left = i;
        }
    }
    sum = max;
    int right = m;
    for (int i = m+1; i < h; i++) {
        sum += a[i];
        if (sum > max) {
            max = sum;
            right = i;
        }
    }
    return make_tuple(max, left, right);
}

template<typename T>
tuple<T, int, int> find_pair (T *a, int l, int h) {
    tuple<T, int, int> ma, mb, mc;
    if (l < h) {
        int m = (l+h) / 2;
        ma = find_pair(a, l, m);
        mb = find_pair(a, m+1, h);
        mc = find_pair_mid(a, l, h);
    
        return  max(ma, max(mb, mc));
    }
    else
        return make_tuple(T(-10000), l, h);
}

// B1
template<typename T>
pair<int, int> mcs(T* a, int n, T& maxsum) {
    tuple<T, int, int> t = find_pair(a, 0, n-1);
    maxsum = get<0>(t);
    if (get<1>(t) == get<2>(t))
        return make_pair(1, 0);
    return make_pair(get<1>(t), get<2>(t));
}

// B2
template<typename T, int n>
pair<int, int> mcs(T (&a)[n], T& maxsum) {
    tuple<T, int, int> t = find_pair(a, 0, n-1);
    maxsum = get<0>(t);
    if (get<1>(t) == get<2>(t))
        return make_pair(1, 0);
    return make_pair(get<1>(t), get<2>(t));
}


template<typename T>
tuple<int, int , typename iterator_traits<T>::value_type>
mcs_scan(T a, int n) {
    int f, b, c, cm;
    cm = c = f = 0;
    typename iterator_traits<T>::value_type sum, max;   // WTF ...
    sum = max = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
        c++;
        if (sum > max) {
            max = sum;
            f = i;
            cm = c;
        }
        else if (sum < 0) {
            c = sum = 0;
        }
    }
    b = f - cm + 1;
    return make_tuple(b, f, max);
}




template<typename T>
inline void showmcs(char c,const tuple<int,int,T>& p)
{
	cout << get<2>(p) << " : ";
	if (get<0>(p)<=get<1>(p))
		cout << c << "[" << get<0>(p) << ".." << get<1>(p) << "] is an mcs.\n";
	else
		cout << "An empty sequence is an mcs.\n";
}


int main()
{
	int a[13]={38,-62,47,-33,28,13,-18,-46,8,21,12,-53,25};  
	double b[10]={3.1,-4.1,5.9,2.6,-5.3,5.8,9.7,-9.3,-2.3,8.4};   
	int c[8]={1,2,3,-100,3,3,-20,6};
	int d[9]={-1,-2,-3,-4,-5,-6,-7,-8,-9};
	cout << "Testing algorithm B1\n";
	{ int maxsum; pair<int,int> p=mcs(a,13,maxsum); showmcs('a',make_tuple(p.first,p.second,maxsum)); }
	{ double maxsum; pair<int,int> p=mcs(b,10,maxsum); showmcs('b',make_tuple(p.first,p.second,maxsum)); }
	{ int maxsum; pair<int,int> p=mcs(c,8,maxsum); showmcs('c',make_tuple(p.first,p.second,maxsum)); }
	{ int maxsum; pair<int,int> p=mcs(d,9,maxsum); showmcs('d',make_tuple(p.first,p.second,maxsum)); }

	cout << "\nTesting algorithm B2: Metaprogram\n";
	{ int maxsum; pair<int,int> p=mcs(a,maxsum); showmcs('a',make_tuple(p.first,p.second,maxsum)); }
	{ double maxsum; pair<int,int> p=mcs(b,maxsum); showmcs('b',make_tuple(p.first,p.second,maxsum)); }
	{ int maxsum; pair<int,int> p=mcs(c,maxsum); showmcs('c',make_tuple(p.first,p.second,maxsum)); }
	{ int maxsum; pair<int,int> p=mcs(d,maxsum); showmcs('d',make_tuple(p.first,p.second,maxsum)); }

	cout << "\nTesting algorithm C\n";
	showmcs('a',mcs_scan(a,13)); 
	showmcs('b',mcs_scan(b,10)); 
	showmcs('c',mcs_scan(c,8)); 
	showmcs('d',mcs_scan(d,9));
}
