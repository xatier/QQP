template<class T>
class list {
public:
// types
	class iterator; 
	class const_iterator;
  	typedef T* pointer;
  	typedef const T* const_pointer;
  	typedef T& reference;
  	typedef const T& const_reference;  
// ctor/dtor
  	list();
	list(const list<T>&);
	template<class U> list(list<U>&);
	template<class InputIterator> list(InputIterator,InputIterator);
  	~list();
// modifiers
  	iterator insert(iterator,const T& =T());
  	iterator erase(iterator);
  	void push_front(const T& d) { insert(begin(),d); }
  	void push_back(const T& d) { insert(end(),d); }
  	void pop_front() { erase(begin()); }
  	void pop_back() { erase(--end()); }
	void splice(iterator,list<T>&);
// list operations
  	void remove(const T&);
// capacity
  	bool empty() const { return begin()==end(); }
// element access
  	reference front() { return *begin(); }
  	const_reference front() const { return *begin(); }
	reference back() { return *--end(); }
  	const_reference back() const { return *--end(); }
// iterator					
  	iterator begin() { return head->succ; }
  	const_iterator begin() const { return head->succ; }
  	iterator end() { return head; }
  	const_iterator end() const { return head; }
private:
  	struct node;
  	node* head;
};

template<class T>
struct list<T>::node
{
   	T datum;
	node *pred,*succ;
   	node(const T& d,node* p,node* s)  
   	: datum(d), pred(p), succ(s)
   	{}
};

template<class T>
class list<T>::const_iterator {
public:
	const_iterator(const node* cur=0) : current(cur) {}
	//const_iterator(iterator it) : current(it.current) {}   // conversion (1)
	const_reference operator*() const { return current->datum; }
	const_pointer operator->() const { return &operator*(); } 
	const_iterator& operator++() { current=current->succ; return *this; }
	const const_iterator operator++(int) { iterator old=*this; ++*this; return old;  } 
	const_iterator& operator--() { current=current->pred; return *this; }
	const const_iterator operator--(int) { iterator old=*this; --*this; return old;  }  
	bool operator==(const_iterator it) const { return current==it.current; }
	bool operator!=(const_iterator it) const { return current!=it.current; }
private:
	const node* current;  		
};

template<class T>
class list<T>::iterator {
	friend class list<T>;									// modifier (1)
	//friend class const_iterator;							// conversion (1)
public:
	//operator node*() const { return current; }			// modifier (2)
	operator const_iterator() const { return current;  }	// conversion (2)
	iterator(node* cur=0) : current(cur) {}
	reference operator*() const { return current->datum; }
	pointer operator->() const { return &(operator*()); } 
	iterator& operator++() { current=current->succ; return *this; }
	const iterator operator++(int) { iterator old=*this; ++*this; return old;  } 
	iterator& operator--() { current=current->pred; return *this; }
	const iterator operator--(int) { iterator old=*this; --*this; return old;  }  
	bool operator==(iterator it) const { return current==it.current; }
	bool operator!=(iterator it) const { return current!=it.current; }
private:
	node* current;
};

// ctor
template<class T>
list<T>::list()
: head((node*)operator new(sizeof(node)))
{  	
	head->pred=head->succ=head;  
}

template<class T>
template<class InputIterator> 
list<T>::list(InputIterator first,InputIterator last)
: head((node*)operator new(sizeof(node)))
{  	
	head->pred=head->succ=head; 
	while (first!=last) { push_back(*first); ++first; }
};

// copy ctor
template<class T>
list<T>::list(const list<T>& rhs)
: head((node*)operator new(sizeof(node)))
{ 	
	head->pred=head->succ=head;  
	node* q=rhs.head->succ;
	while (q!=rhs.head) { push_back(q->datum); q=q->succ; }
}

// dtor
template<class T>
list<T>::~list()
{ 
	while (!empty()) pop_back();   
  	operator delete(head);
} 

// modifier (1)
template<class T> 
typename list<T>::iterator list<T>::insert(iterator pos,const T& d)
{
  	node* p=new node(d,pos.current->pred,pos.current);
  	pos.current->pred->succ=p;
  	pos.current->pred=p;
  	return p; 		
}

template<class T>
typename list<T>::iterator list<T>::erase(iterator pos)
{
  	node* p=pos.current;
  	++pos;
  	p->pred->succ=p->succ;
  	p->succ->pred=p->pred;
  	delete p;
  	return pos;
}

// modifier (2)
//template<class T> 
//typename list<T>::iterator list<T>::insert (iterator pos,const T& d)
//{                                        
//	node* p=new node(d,((node*)pos)->pred,pos);
//	((node*)pos)->pred->succ=p;
//	((node*)pos)->pred=p;	
//	return p; 		
//}
//
//template<class T>
//typename list<T>::iterator list<T>::erase(iterator pos)
//{
//	node* p=pos;  			
//	++pos;
//	p->pred->succ=p->succ;
//	p->succ->pred=p->pred;
//	delete p;
//	return pos;
//}

// list operations
template<class T>
void list<T>::remove(const T& value)
{
	for (iterator it=begin();it!=end();)
		if (*it==value) it=erase(it);
		else ++it;
}

// Splice (1)
template<class T>
void list<T>::splice(iterator pos,list<T>& x)
{
	pos.current->pred->succ=x.head->succ;
	x.head->succ->pred=pos.current->pred;
	x.head->pred->succ=pos.current;
	pos.current->pred=x.head->pred;
	x.head->succ=x.head->pred=x.head;
}

// Splice (2)
//template<class T>
//void list<T>::splice(iterator pos,list<T>& x)
//{
//	((node*)pos)->pred->succ=x.head->succ;
//	x.head->succ->pred=((node*)pos)->pred;
//	x.head->pred->succ=pos;
//	((node*)pos)->pred=x.head->pred;
//	x.head->succ=x.head->pred=x.head;
//}

// converting ctor
template<class T>
template<class U> 
list<T>::list(list<U>& rhs)
: head((node*)operator new(sizeof(node)))
{  	
	head->pred=head->succ=head; 
	list<U>::iterator it=rhs.begin();
	while (it!=rhs.end()) {
		push_back(*it); ++it;
		if (it!=rhs.end()) it=rhs.erase(it);
	}
}