#include "deque6.h"

template<typename T,typename Container=deque<T> >
class stack {
public: 
// types
	typedef typename Container::value_type value_type;
	typedef typename Container::size_type size_type;
	typedef typename Container::reference reference;
	typedef typename Container::const_reference const_reference;
// ctor
	stack(const Container& =Container());
	stack(stack&&);   // omit this in GNU C++
// modifiers
	void push(const value_type&);
	void push(value_type&&);
	void pop();
// element access
    reference top();
	const_reference top() const;
// capacity
	bool empty() const;
    size_type size()  const;
private:		
	Container c;
}; 

template<typename T,typename Container>
stack<T,Container>::stack(const Container& c) : c(c) {}

template<typename T,typename Container>
stack<T,Container>::stack(stack&& s) : c(std::move(s.c)) {} 

template<typename T,typename Container>
void stack<T,Container>::push(const value_type& x) { c.push_back(x); }

template<typename T,typename Container>
void stack<T,Container>::push(value_type&& x) { c.push_back(std::move(x)); }

template<typename T,typename Container>
void stack<T,Container>::pop() { c.pop_back(); }

template<typename T,typename Container>
typename stack<T,Container>::reference stack<T,Container>::top() { return c.back(); }

template<typename T,typename Container>
typename stack<T,Container>::const_reference stack<T,Container>::top() const 
{ 
	return c.back(); 
}

template<typename T,typename Container>
bool stack<T,Container>::empty() const { return c.empty(); }

template<typename T,typename Container>
typename stack<T,Container>::size_type stack<T,Container>::size() const 
{ 
	return c.size(); 
}

