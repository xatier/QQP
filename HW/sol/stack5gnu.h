template<typename T>
class stack {
public:
// types
	typedef size_t size_type;
	typedef T value_type;
// ctors and dtor
	stack(size_type=2);
	~stack();
	stack(const stack<T>&);
// stack operations
	void push(const value_type&);
	void pop();
	value_type& top();
	const value_type& top() const;
	size_type size() const;
	bool empty() const;
private:
	struct node;
	node* head=nullptr;		// deafult value
	int _top;
	const size_type sz;
	size_type _size;
	void copy(node* p);
};

template<typename T>
struct stack<T>::node {
	node(T*,node*);
	T* stk;
	node* succ;
};

template<typename T>
stack<T>::node::node(T* t,node* s) : stk(t), succ(s) {}

template<typename T>
stack<T>::stack(size_type sz) 
: _top(sz-1), sz(sz), _size(0)		// head(nullptr) is optional
{} 

template<typename T>
stack<T>::~stack() { while (!empty()) pop(); }

template<typename T>
bool stack<T>::empty() const { return head==nullptr; }

template<typename T>
typename stack<T>::value_type& stack<T>::top()
{ 
	return head->stk[_top]; 
}
template<typename T>
const typename stack<T>::value_type& stack<T>::top() const
{ 
	return head->stk[_top]; 
}

template<typename T>
typename stack<T>::size_type stack<T>::size() const
{
	return _size;
}

template<typename T>
void stack<T>::push(const value_type& n)
{
	if (_top==sz-1) {
		head=new node((T*) operator new[](sz*sizeof(T)),head); 
		_top=-1;
	}
	++_top;
	new (head->stk+_top) T(n);
	_size++;
}

template<typename T>
void stack<T>::pop()
{
	head->stk[_top].~T();
	_top--; _size--;
	if (_top==-1) {
		node* p=head; 
		head=head->succ; 
		operator delete[](p->stk); delete p; _top=sz-1;
	}
}

template<typename T>
stack<T>::stack(const stack<T>& rhs)	// delegating ctor
: stack<T>(rhs.sz)
{
	if (rhs.head!=nullptr) {
		copy(rhs.head->succ);
		for (int i=0;i<=rhs._top;i++) push(rhs.head->stk[i]);
	}
}

template<typename T>
void stack<T>::copy(node* p)
{
	if (p!=nullptr) {
		copy(p->succ);
		for (size_type i=0;i<sz;i++) push(p->stk[i]);
	}
}
