
template<typename T>
class deque { 
public:
// types
	typedef T        value_type;
	typedef size_t   size_type;
	typedef T&       reference;
	typedef const T& const_reference;

// ctor/copy ctor/dtor
	deque();
	deque(const deque&);
	deque(deque&&);           // move stor
	~deque();

// capacity
	size_type size(void)  const {return _size;}
	bool      empty(void) const {return _size == 0;}

// modifiers 
	void push_front (const T&); 
    void push_front (T&&); 
	void push_back  (const T&);
	void push_back  (T&&); 
	void pop_front  (void); 
	void pop_back   (void);

// element access
	reference       front(void)       {return head->succ->datum;}
	const_reference front(void) const {return head->succ->datum;}
	reference       back(void)        {return head->pred->datum;}
	const_reference back(void)  const {return head->pred->datum;}

// debug
    void dump(void);

private:
	struct node;
	node *head;
	size_type _size;
};


template<typename T>
struct deque<T>::node {
	node(const T&,node*, node*);
	node(T&&,node*,node*);
	T datum;
	node *pred,*succ;
};


template<typename T>
deque<T>::node::node (const T& d, node *p, node *s) :
    datum(d), pred(p), succ(s) { }

template<typename T>
deque<T>::node::node (T&& d, node *p, node *s) :
    datum(std::move(d)), pred(p), succ(s) { }


template<typename T>
deque<T>::deque () : 
    head((node *)operator new (sizeof(node))), _size(0) {
    // create a new node
    head->pred = head->succ = head;
}


template<typename T>
deque<T>::deque (const deque& rhs) : 
    head((node *)operator new (sizeof(node))), _size(0) {
    // initial this->head as a new node
    head->pred = head->succ = head;

    // push nodes one by one
    node *p = rhs.head->succ;
    while (p != rhs.head) {
        push_back(p->datum);
        p = p->succ;
    }
}


template<typename T>
deque<T>::deque (deque&& rhs) : 
    head((node *)operator new (sizeof(node))), _size(rhs._size) {
    
    head->succ = rhs.head->succ;
    rhs.head->succ->pred = head;

    head->pred = rhs.head->pred;
    rhs.head->pred->succ = head;

    // make rhs as a brain new deque
    rhs.head->pred = rhs.head;
    rhs.head->succ = rhs.head;
    rhs._size = 0;

}


template<typename T>
void deque<T>::push_front (const T& d) {
    node *n = new node(d, head, head->succ);
    head->succ->pred = n;
    head->succ       = n;
    _size++;
}


template<typename T>
void deque<T>::push_front (T&& d) {
    node *n = new node(std::move(d), head, head->succ);
    head->succ->pred = n;
    head->succ       = n;
    _size++;
}


template<typename T>
void deque<T>::push_back (const T& d) {
    node *n = new node(d, head->pred, head);
    head->pred->succ = n;
    head->pred       = n;
    _size++;
}


template<typename T>
void deque<T>::push_back (T&& d) {
    node *n = new node(std::move(d), head->pred, head);
    head->pred->succ = n;
    head->pred       = n;
    _size++;
}


template<typename T>
void deque<T>::pop_front (void) {
    node *n = head->succ;
    head->succ = n->succ;
    head->succ->pred = head;
    delete n;
    _size--;
}


template<typename T>
void deque<T>::pop_back (void) {
    node *n = head->pred;
    head->pred = n->pred;
    head->pred->succ = head;
    delete n;
    _size--;
}


template<typename T>
void deque<T>::dump (void) {
    node *p = head->succ;
    while (p != head) {
        std::cout << p->datum << ", ";
        p = p->succ;
    }
}


template<typename T>
deque<T>::~deque () {
    while (!empty())
        pop_back();
    operator delete (head);
}
