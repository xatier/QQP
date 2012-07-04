template<typename T>
class stack {
public:
	typedef size_t size_type;
	typedef T value_type;
	stack();
	~stack() { while (!empty()) pop(); operator delete[](stk); }
	void push(const value_type&);
	void pop();
	value_type& top() { return stk[_top]; } 
	const value_type& top() const { return stk[_top]; }
	size_type size() const { return _top+1; }
	bool empty() const { return size()==0; } 
private:
	T* stk;
	size_type _top,_capacity;
};

template<typename T>
stack<T>::stack() : stk(NULL), _top(-1), _capacity(0) {} 

template<typename T>
void stack<T>::push(const value_type& n)
{
	if (_capacity==0) {
		_capacity=1;
		stk=(T*)operator new[](_capacity*sizeof(T));
	} else if (_top+1==_capacity) { 
		_capacity*=2;
		T* old_stk=stk;
		stk=(T*)operator new[](_capacity*sizeof(T));
		for (size_type i=0;i<=_top;i++)
			new (stk+i) value_type(old_stk[i]);
		for (size_type i=_top+1;i>0;i--)
			old_stk[i-1].~T();
		operator delete[](old_stk);
	}
	_top++;
	new (stk+_top) value_type(n);
}

template<typename T>
void stack<T>::pop(){ stk[_top].~T(); _top--; }
