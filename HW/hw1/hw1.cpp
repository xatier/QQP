/* ----------------------------------------- *
|   QQP homework #1                          |
|   Binary quicksort (Radix-exchange sort)   |
|   Due date:  3/22                          |
|   0016045 ymli @ cs104                     |
* ----------------------------------------- */

#include <iostream>
#include <limits>
#include <climits>

using namespace std;


template<typename T>
void binary_qsort (T *a, int n);

template<>
void binary_qsort (float* a, int n);

template<typename T>
int partition (T* a, int l, int h, int b, int pivot);

template<typename T>
void binary_qsort (T* a, int l, int h, int b);


template<typename T>
int partition (T* a, int l, int h, int b, int pivot) {
    int i = l, j = h;
    while (i <= j) {
        if (static_cast<int>(a[i] >> b & 1) != pivot) {
            i++;
        }
        else {
            T z = a[i]; a[i] = a[j]; a[j] = z;
            j--;
        }
    }
    return i;
}


template<typename T>
void binary_qsort (T *a, int l, int h, int b) {
    if (l < h) {
        int m;
        if (numeric_limits<T>::is_signed ) {
            if (b == 8 * sizeof(signed) - 1) {
                m = partition(a, l, h, b, 0); 
            }
            else {
                m = partition(a, l, h, b, 1); 
            }
        }
        else {
            m = partition(a, l, h, b, 1); 
        }
        binary_qsort(a,   l, m-1, b-1);
        binary_qsort(a, m,   h, b-1);

    }
}


template <typename T>
void binary_qsort (T *a, int n) {
    if (numeric_limits<T>::is_signed) {
        // cout << "i am signed\n";
        binary_qsort(a, 0, n-1, 8*sizeof(signed)-1);
    }
    else {
        // cout << "i am unsigned\n";
        binary_qsort(a, 0, n-1, 8*sizeof(unsigned)-1);
    }
}


void binary_qsort (float *a, int l, int h, int b) {
    int* x = reinterpret_cast<int*>(a);
    if (l < h) {
        int m;
        if (b == 31) {
            m = partition(x, l, h, b, 0); 
        }
        else {
            if (a[l] < 0) {
                m = partition(x, l, h, b, 0); 
            }
            else {
                m = partition(x, l, h, b, 1); 
            }
        }
        binary_qsort(a,   l, m-1, b-1);
        binary_qsort(a, m,   h, b-1);
    }
}

template <>
void binary_qsort (float *a, int n) {
    // cout << "i am float\n";
    binary_qsort(a, 0, n-1, 8*sizeof(float)-1);
}



int main(void)

{

    unsigned a[11]={UINT_MAX,777,INT_MAX,7,999999999,INT_MAX+1u,7777777,88888888,INT_MAX-1,77,UINT_MAX-1};

    binary_qsort(a,11);

    for (int i=0;i<11;i++) cout << a[i] << ' ';

    cout << endl << endl;

    

    unsigned char b[15]={177,129,66,188,166,255,99,128,127,254,77,88,199,55,155};

    binary_qsort(b,15);

    for (int i=0;i<15;i++) cout << (unsigned)b[i] << ' ';

    cout << endl << endl;


    

    signed c[16]={-7777777,INT_MAX,777,-88888888,INT_MIN,-777,7,999999999,

                  INT_MAX-1,7777777,-7,-999999999,88888888,77,INT_MIN+1,-77};

    binary_qsort(c,16);



    for (int i=0;i<16;i++) cout << c[i] << ' ';

    cout << endl << endl;



    float d[21]={numeric_limits<float>::infinity(),7.7f,5.5f,-1.1f,-3.3f,8.8f,-2.2f,9.9f,-6.6f,-4.4f,

                -numeric_limits<float>::infinity(),0.0f,-7.7f,-5.5f,1.1f,3.3f,-8.8f,2.2f,-9.9f,6.6f,4.4f};

    binary_qsort(d,21);

    for (int i=0;i<21;i++) cout << d[i] << ' ';

    cout << endl;

}

 
