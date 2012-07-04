#include <iostream>

template<typename T>
class stack {
public:
// types
	typedef size_t size_type;
	typedef      T value_type;
// ctors and dtor
	stack  (size_type=2);
	~stack (void);
	stack  (const stack<T>&);
// stack operations
	void push (const value_type&);
	void pop  (void);
//top
          value_type& top (void)       {return head->stk[_top];}
	const value_type& top (void) const {return head->stk[_top];}

	size_type size (void) const {return _size;}
	bool     empty (void) const {return _size == 0;}


private:
	struct node;
	node*  head;
	int    _top;

	const size_type sz;
	size_type    _size;

    void copy (node *p);

};


template<typename T>
struct stack<T>::node {
    node(T*,node*);   // ctor
    ~node();
    T* stk;
    node* succ;
};



template<typename T>
stack<T>::node::node (T *d, node *s) : 
    stk(d), succ(s) {}


template<typename T>
stack<T>::node::~node () {
    operator delete [] (stk);
}


template<typename T>
stack<T>::stack (size_type size) : 
    head((node *)operator new (sizeof(node))), _top(-1), 
    sz(size), _size(0) {
    //  allocate space for where head point to
    head->stk  = (T *)operator new [] (sizeof(T) * sz);
    head->succ = NULL;
}

/* method A: iteration method */
/*
template<typename T>
stack<T>::stack(const stack& rhs)
: head((node *)operator new (sizeof(node))), sz(rhs.sz) {
    node *q = rhs.head;
    head->stk  = (T *)operator new [] (sizeof(T) * sz);
    head->succ = NULL;
    node *p = head;

    while (q != NULL) {
        for (int i = 0; i < (int)sz; i++)
            p->stk[i] = q->stk[i];
        p->succ = (node *)operator new (sizeof(node));
        p->succ->stk = (T *)operator new [] (sizeof(T) * sz);
        p->succ->succ = NULL;
        p = p->succ;
        q = q->succ;
    }
    this->_size = rhs._size;
    this->_top = rhs._top;
}
*/


/* method B: recursion method */
template<typename T>
stack<T>::stack(const stack<T>& rhs) :
    head((node *)operator new (sizeof(node))), sz(rhs.sz) {
    // allocate a node for this->head
    head->stk  = (T *)operator new [] (sizeof(T) * sz);
    head->succ = NULL;
    copy(rhs.head);

    // fix the this->_size and this->_top
    this->_size = rhs._size;
    this->_top = rhs._top;
}


template<typename T>
void stack<T>::copy(node *p) {
    if (p != NULL) {
        // go to the bottom of the stack
        copy(p->succ);
        // copy elements one by one
        for (int i = 0; i < (int)sz; i++)
            this->push(p->stk[i]);
    }
}


template<typename T>
void stack<T>::push (const T& value) {
    // XXX: i don't know why it will failed 
    // if i din't add on (int) type conversion on it
    if (_top < (int)sz-1) {
    // i have enough free space
        head->stk[++_top] = value;
    }
    else {
    // allocate new node for it
        _top = -1;
        node* k = (node *)operator new    (sizeof(node));
        k->stk  =    (T *)operator new [] (sizeof(T) * sz);
        k->stk[++_top] = value;
        k->succ        = head;

        head = k;
    }
    _size++;
}


template<typename T>
void stack<T>::pop (void) {
    // don't need to delete the node
    if (_top > 0) {
        _top--;
    }
    else {
    // chomp off ur head!!
        _top = sz-1;
        node* k = head;
        head = k->succ;
        k->~node();
    }
    _size--;
}


template<typename T>
stack<T>::~stack () {
    // pop all elements out untill the stack is empty
    while (!empty())
        pop();
    operator delete (head);
}
