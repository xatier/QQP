#include <initializer_list>
using namespace std;

template<typename T>
class vector {
public:
// types
  	typedef size_t size_type;
  	typedef T& reference;
  	typedef const T& const_reference;
	typedef T* iterator;
	typedef const T* const_iterator;
// ctor/copy ctor/dtor
	vector();
	explicit vector(size_type);	
	template<typename InputIterator> 
	vector(InputIterator,InputIterator);
	vector(size_type,const T&);
	vector(const vector&);  
	vector(vector&&);
	vector& operator=(const vector&);
	vector<T>& operator=(vector<T>&&);			
	vector(initializer_list<T>);			
  	~vector();
// iterators
	iterator begin() { return start; }
	const_iterator begin() const { return start; }
	iterator end() { return finish; }
	const_iterator end() const { return finish; }
	const_iterator cbegin() const { return start; }		
	const_iterator cend() const { return finish; }		
// modifiers
	iterator insert(const_iterator,const T&);
	iterator insert(const_iterator,T&&);			
	iterator erase(const_iterator);					
  	void push_back(const T& val) { insert(end(),val); }
	void push_back(T&& val) { insert(end(),std::move(val)); }
	void pop_back() { erase(end()-1); }
	template<typename Predicate>
	void remove_if(Predicate);
// capacity
  	size_type size() const { return finish-start; }
	size_type capacity() const { return end_storage-start; }
	bool empty() const { return size()==0; }
// element access
  	reference operator[](size_type n) { return start[n]; } 
	const_reference operator[](size_type n) const { return start[n]; } 
	reference back() { return *(end()-1); }
	const_reference back() const { return *(end()-1); }
private:
	T *start,*finish,*end_storage;
};

// ctor
template<typename T>
vector<T>::vector() 
: start(nullptr),finish(nullptr),end_storage(nullptr)  
{}
	
template<typename T>
vector<T>::vector(size_type n)
: start((T*)operator new[](n*sizeof(T))),
  finish(start+n),end_storage(start+n)
{
	//for (T* it=start;it!=finish;++it) new (it) T();
	for (T& var : *this) new (&var) T();
} 

template<typename T>
vector<T>::vector(size_type n,const T& val)
: start((T*)operator new[](n*sizeof(T))),
  finish(start+n),end_storage(start+n)
{
	//for (T* it=start;it!=finish;++it) new (it) T(val);
	for (T& var : *this) new (&var) T(val);
} 

template<typename T>
vector<T>::vector(initializer_list<T> init)
: start((T*)operator new[](init.size()*sizeof(T))),
  finish(start+init.size()),end_storage(start+init.size())
{ 
	//iterator it=begin();
	//const_iterator cit=init.begin();
	//while (cit!=init.end()) {
	//	new (it) T(*cit); ++it; ++cit;
	//}
	iterator it=begin();
	for (auto & val : init) new (it++) T(val);
} 

// dtor
template<typename T>
vector<T>::~vector() 
{ 
	//for (T* it=start;it!=finish;++it) it->~T();
	for (T& it : *this) (&it)->~T();
  	operator delete[](start); 
}

// copy ctor
template<typename T>
vector<T>::vector(const vector<T>& rhs)
: start(nullptr),finish(nullptr),end_storage(nullptr)  
{
  	if (!rhs.empty()) {
		start=(T*)operator new[](rhs.capacity()*sizeof(T));
		finish=start+rhs.size();
		end_storage=start+rhs.capacity();
		for (size_type i=0;i<rhs.size();i++) 
		new (start+i) T(rhs.start[i]);
  	} 
}

// move ctor
template<typename T>
vector<T>::vector(vector<T>&& rhs)
: start(rhs.start),finish(rhs.finish),end_storage(rhs.end_storage)
{
	rhs.start=rhs.finish=rhs.end_storage=nullptr;
}

// copy assignment operator
template<typename T>
vector<T>& vector<T>::operator=(const vector<T>& rhs) 
{
	if (this!=&rhs) {
		if (capacity()<rhs.size()) {
			this->~vector();  
			start=(T*)operator new[](rhs.capacity()*sizeof(T));
			finish=start+rhs.size();
			end_storage=start+rhs.capacity();
			for (size_type i=0;i<rhs.size();i++) new (start+i) T(rhs.start[i]);
		} else if (size()<=rhs.size()) {
			for (size_type i=0;i<size();i++) start[i]=rhs.start[i];
			for (size_type i=size();i<rhs.size();i++) new (finish++) T(rhs.start[i]);
		} else {
			for (size_type i=0;i<rhs.size();i++) start[i]=rhs.start[i];
			for (size_type i=size();i>rhs.size();i--)  (--finish)->~T();
		}
	}
	return *this;
}

// move assignment operator
template<typename T>
vector<T>& vector<T>::operator=(vector<T>&& rhs) 
{
	if (this!=&rhs) {
		this->~vector();
		start=rhs.start; finish=rhs.finish; end_storage=rhs.end_storage;
		rhs.start=rhs.finish=rhs.end_storage=nullptr;
	}
	return *this;
}

// modifiers
template<typename T>
typename vector<T>::iterator vector<T>::insert(const_iterator pos,const T& val)
{
	if (capacity()==size()) {
		size_type n=capacity()==0?1:2*capacity();
		T* first=(T*)operator new[](n*sizeof(T));
		for (iterator it=begin();it!=pos;++it) 
			new (first+(it-start)) T(std::move(*it));
		iterator new_pos=first+(pos-start);
		new (first+(pos-start)) T(val);
		for (iterator it=const_cast<iterator>(pos);it!=end();++it) 
			new (first+(it-start)+1) T(std::move(*it));
		size_type sz=size();
  		this->~vector();
  		start=first;
  		finish=start+sz+1;
		end_storage=start+n;
		return new_pos;
	} else {
		iterator new_pos=const_cast<iterator>(pos);
		if (new_pos==end()) new (finish) T(val);
		else {
			new (finish) T(std::move(*(finish-1))); 
			for (iterator it=finish-1;it!=pos;--it) *it=std::move(*(it-1));
			*new_pos=val;
		}
		finish++;
		return new_pos;
	}
}

template<typename T>
typename vector<T>::iterator vector<T>::insert(const_iterator pos,T&& val)
{
	if (capacity()==size()) {
		size_type n=capacity()==0?1:2*capacity();
		T* first=(T*)operator new[](n*sizeof(T));
		for (iterator it=begin();it!=pos;++it) 
			new (first+(it-start)) T(std::move(*it));
		iterator new_pos=first+(pos-start);
		new (first+(pos-start)) T(std::move(val));
		for (iterator it=const_cast<iterator>(pos);it!=end();++it) 
			new (first+(it-start)+1) T(std::move(*it));
		size_type sz=size();
  		this->~vector();
  		start=first;
  		finish=start+sz+1;
		end_storage=start+n;
		return new_pos;
	} else {
		iterator new_pos=const_cast<iterator>(pos);
		if (new_pos==end()) new (finish) T(std::move(val));
		else {
			new (finish) T(std::move(*(finish-1))); 
			for (iterator it=finish-1;it!=pos;--it) *it=std::move(*(it-1));
			*new_pos=std::move(val);
		}
		finish++;
		return new_pos;
	}
}

template<typename T>
typename vector<T>::iterator vector<T>::erase(const_iterator pos)
{
	iterator new_pos=const_cast<iterator>(pos);
	for (iterator it=new_pos+1;it!=end();it++) *(it-1)=std::move(*it);
	(--finish)->~T();
	return new_pos;
}



