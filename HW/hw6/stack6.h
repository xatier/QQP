#include "deque6.h"

template<typename T, typename Container=deque<T> >
class stack {
public: 
// types
	typedef typename Container::value_type      value_type;
	typedef typename Container::size_type       size_type;
	typedef typename Container::reference       reference;
	typedef typename Container::const_reference const_reference;

// ctor
    stack (const Container& _c);
	stack (Container&& _c = Container());
	//stack(stack&&);   // omit this in GNU C++

// modifiers
	void push (const value_type&);
	void push (     value_type&&);
	void pop  (void);

// element access
          reference top (void)       { return c.back(); }
	const_reference top (void) const { return c.back(); }

// capacity
	bool    empty (void) const { return c.empty(); }
    size_type size(void) const { return c.size();  }

private:		
	Container c;
}; 


template<typename T, typename Container >
stack<T, Container>::stack (const Container& _c) : 
    c(_c) { }


template<typename T, typename Container >
stack<T, Container>::stack (Container&& _c) : 
    c(std::move(_c)) { }


template<typename T, typename Container >
void stack<T, Container>::push (const value_type& d) {
    c.push_back(d);
}


template<typename T, typename Container >
void stack<T, Container>::push (value_type&& d) {
    c.push_back(std::move(d));
}


template<typename T, typename Container >
void stack<T, Container>::pop (void) {
    c.pop_back();
}

