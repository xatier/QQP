#include <iostream>
#include <limits>
using namespace std;




int main()
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
 