/* ----------------------------------------- *
|   QQP homework #3                          |
|   Heapsort                                 |
|   Due date:  4/12                          |
|   0016045 ymli @ cs104                     |
* ----------------------------------------- */

#include <iostream>
#include <algorithm>
#include <cstring>
        
using namespace std;

template <typename T, typename Compare>
void heapify (T *h, int n, int k, Compare comp) {
    int l, r, haha;
    l = [](int x) {return 2*x;}(k);
    r = [](int x) {return 2*x+1;}(k);

    if (l <= n && comp(h[l], h[k])) {
        haha = l;
    }
    else {
        haha = k;
    }
    if (r <= n && comp(h[r], h[haha]))
        haha = r;
    if (haha != k) {
        swap(h[k], h[haha]);
        heapify(h, n, haha, comp);
    }
}


template<typename T, typename Compare>
void buildheap (T *a, int n, Compare comp) {
    for (int k = n/2 - 1; k >= 0; k--)
        heapify(a, n, k, comp);
}

template<typename T, typename Compare>
void heapsort (T *a, T *b, Compare comp) {
    int n = b-a;
    buildheap(a, n, comp);

    for (int k = n-1; k >= 1; k--) {
        swap(a[0], a[k]);
        heapify(a, k-1, 0, comp);
    }
}


template <typename T>
class print {
    public: void operator () (const T &n) {
        cout << n << ' '; 
    }
};

template <typename T>
class my_cmp {
    public : bool operator () (T *x, T *y) {
        return (strcmp(x, y) < 0);
    }
};

int main()
{

    int a[15]={4,5,2,5,4,3,5,4,1,3,3,5,5,4,2};
    heapsort(a,a+15,greater_equal<int>());

    for_each(a, a+14, print<int>());
    cout << endl;

    char b[]="SnoopyLikesC++!Crazy!";
    heapsort(b,b+sizeof(b)-1,[](int x, int y) {return x <= y;});
    cout << b << endl;
    

    function<bool(const char *, const char *)> comp[2] = {
        [](const char *x, const char *y){return (strcmp(y, x) < 0);},
        my_cmp<const char >()
    };

    for (int i=0;i<2;i++) {
        const char* c[11]={"Knicks","Lakers","76ers","Hawks",
            "Bulls","Mavericks","Heat","Wizards",
            "Bucks","Pacers","Magic"};
        heapsort(c,c+11,comp[i]);
        for_each(c, c+11, print<const char *>());
        cout << endl ;
    }

    return 0;
}
