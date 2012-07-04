#include <iostream>
#include <cstring>
using namespace std;

class String {
public:
// types
 	typedef size_t size_type;
	typedef char&  reference;
 	typedef const char& const_reference;
// ctor/copy/dtor
 	String(const char* ="");
	String(const String&);
	String(String&&);
	~String();
 	String& operator=(const String&);
 	String& operator=(String&&);
// String operations
	const char* c_str() const { return _data; }
// modifiers
	String& operator+=(const String&);
	String& insert(size_type,const String&);
// element access
	reference operator[](size_type pos) { return _data[pos]; }
 	const_reference operator[](size_type pos ) const { return _data[pos]; }
// capacity
	size_type capacity() const { return _capacity; }
 	size_type size() const { return _size; }
	bool empty() const { return _size==0; }
private:
	size_type _size,_capacity;
 	char* _data;
	size_type _cap(size_type);
}; 

// ctor/dtor
String::~String() { delete [] _data; }

String::String(const char* s)
: _size(strlen(s)),
  _capacity(_cap(_size)),
  _data(strcpy(new char[_capacity+1],s)) 
{}

String::size_type String::_cap(size_type sz)
{
	size_type cap=15;									
	while (cap<sz) (cap<<=1)++;
	return cap;
}

// copy ctor
String::String(const String& rhs) 
: _size(rhs._size),
  _capacity(rhs._capacity),
  _data(strcpy(new char[_capacity+1],rhs._data))
{}

// move ctor
String::String(String&& rhs)
: _size(rhs._size),_capacity(rhs._capacity),_data(rhs._data)
{
	rhs._size=rhs._capacity=0; 
	rhs._data=nullptr;
}

// copy assignment
String& String::operator=(const String& rhs)
{
  	if (this!=&rhs) {  	
   	 	delete [] _data;
		_size=rhs._size; _capacity=rhs._capacity;
		_data=strcpy(new char[_capacity+1],rhs._data);
  	}
  	return *this;
}

// move assignment
String& String::operator=(String&& rhs)
{
  	if (this!=&rhs) {  
		delete [] _data;
		_size=rhs._size; _capacity=rhs._capacity;
		_data=rhs._data;
		rhs._size=0; rhs._capacity=0; 
		rhs._data=nullptr;
  	}
  	return *this;
}

// modifiers
String& String::operator+=(const String& rhs)
{
	size_type new_size=_size+rhs._size;
	if (_capacity<new_size) {
		while (_capacity<new_size) (_capacity<<=1)++;
  		char* old_data=_data;
  		_data=strcpy(new char[_capacity+1],old_data);
  		delete [] old_data;
	}                        
//	if (this!=&rhs) strcat(_data,rhs._data); else
	{
	for (size_type i=0;i<rhs._size;i++)
		_data[i+_size]=rhs._data[i];
	_data[new_size]='\0';
	}
	_size=new_size;	
	return *this;
}

// non-member functions
ostream& operator<<(ostream& os,const String& s)
{
	return s.c_str()!=nullptr? os << s.c_str(): os;
}








int main()
{
	String x("Snoopy");
	String a(move(x)),b("Pluto"),c("Garfield");
	cout << a.insert(0,x) << endl;
	cout << a.size() <<  ' ' << a.capacity() << endl;
	cout << x.insert(0,a) << endl;
	cout << x.size() <<  ' ' << x.capacity() << endl;
	cout << a.insert(a.size(),b) << endl;
	cout << a.size() <<  ' ' << a.capacity() << endl;
    cout << a.insert(6,c) << endl;
    cout << a.size() <<  ' ' << a.capacity() << endl;
    cout << b.insert(0,c) << endl;
    cout << b.size() <<  ' ' << b.capacity() << endl;
    cout << b.insert(0,b) << endl;
    cout << b.size() <<  ' ' << b.capacity() << endl;
    cout << a.insert(14,a) << endl;
    cout << a.size() <<  ' ' << a.capacity() << endl;
	cout << c.insert(0,a) << endl;
    cout << c.size() <<  ' ' << c.capacity() << endl;
}

