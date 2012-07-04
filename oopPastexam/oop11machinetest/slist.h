#include <iterator>

class list {
public:
// types
	class iterator;
	class const_iterator;
// ctor/dtor
	list();
	list(const list&);
	~list();
// modifiers
  	iterator insert(iterator,int);
  	iterator erase(iterator);   	
	void push_front(int);
  	void push_back(int);
  	void pop_front();
  	void pop_back();
// iterators
	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;
// capacity
	bool empty() const;
private:
	struct node;
	node* head;
};

struct list::node {
   	node(int d,node* s) : datum(d),succ(s) {}
   	int datum;
   	node* succ;
};

// ctor
list::list() 
: head((node*)operator new(sizeof(node))) 	
{		
	head->succ=head;	
}

// copy ctor
list::list(const list& rhs) 
: head((node*)operator new(sizeof(node))) 
{
	head->succ=head;
	node* q=rhs.head->succ;
	while (q!=rhs.head) { push_back(q->datum); q=q->succ; }
}

// dtor
list::~list()
{
	while (!empty()) pop_front();   
  	operator delete(head);	
}

// iterator
class list::iterator {
	friend class list;
public:
	typedef std::forward_iterator_tag	iterator_category;
	typedef int							value_type;
	typedef ptrdiff_t 					difference_type;
	typedef int* 						pointer;
	typedef int& 						reference;
  	iterator(node* cur=0) : current(cur) {}
	int& operator*() const { return current->datum; 	}
	int* operator->() const { return &operator*(); }
	iterator& operator++() { current=current->succ; return *this; }	
	const iterator operator++(int) { iterator old=*this; ++*this; return old; }
	bool operator==(iterator it) const { return current==it.current; }
  	bool operator!=(iterator it) const { return current!=it.current; }	
private:
  	node* current;
};

// const_iterator
class list::const_iterator {
public:
  	const_iterator(const node* cur=0) : current(cur) {}
	const int& operator*() const { return current->datum; 	}
	const int* operator->() const { return &operator*(); }
	const_iterator& operator++() { current=current->succ; return *this; }	
	const const_iterator operator++(int) { const_iterator old=*this; ++*this; return old; }
	bool operator==(const_iterator it) const { return current==it.current; }
  	bool operator!=(const_iterator it) const { return current!=it.current; }	
private:
  	const node* current;
};

// iterators
list::iterator list::begin() { return head->succ; }
list::const_iterator list::begin() const { return head->succ; }
list::iterator list::end() { return head; }
list::const_iterator list::end() const { return head; }
// capacity
bool list::empty() const { return begin()==end(); }

// modifiers
list::iterator list::insert(iterator pos,int d)
{
	node* p=new node(d,pos.current);
	node* q=head;
	while (q->succ!=pos.current) q=q->succ;
	q->succ=p;
  	return p; 	
}

list::iterator list::erase(iterator pos)
{
  	node* q=head;
	while (q->succ!=pos.current) q=q->succ;
  	q->succ=pos.current->succ;  	// *
  	delete pos.current;
  	return q->succ;
}

void list::push_front(int d) { insert(begin(),d); }
void list::push_back(int d) { insert(end(),d); }
void list::pop_front() { erase(begin()); }
void list::pop_back() 
{ 
	iterator pos;
	for (iterator it=begin();it!=end();pos=it++); 
	erase(pos); 
}

