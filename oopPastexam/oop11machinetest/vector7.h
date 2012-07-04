template<typename T>
class vector {
public:
// types
  	typedef size_t size_type;
  	typedef T& reference;
  	typedef const T& const_reference;
// iterator
	typedef T* iterator;
	typedef const T* const_iterator;
	iterator begin() { return start; }
	const_iterator begin() const { return start; }
	iterator end() { return finish; }
	const_iterator end() const { return finish; }
// ctor/copy ctor/dtor
	vector();
	vector(size_type,const T& =T()); 
  	vector(const vector<T>&); 
  	~vector();
	vector<T>& operator+=(const vector<T>&);
// modifiers
	iterator insert(iterator,const T& =T());
	iterator erase(iterator);
  	void push_back(const T& val) { insert(end(),val); }
	void pop_back() { erase(end()-1); }
// capacity
  	size_type size() const;
	size_type capacity() const;
	bool empty() const;
// element access
  	reference operator[](size_type n); 
	const_reference operator[](size_type n) const;
private:
	T *start, *finish, *end_storage;
};

// ctor
template<typename T>
vector<T>::vector() : start(0), finish(0), end_storage(0)  {}
	
template<typename T>
vector<T>::vector(size_type n,const T& val)
: start((T*)operator new[](n*sizeof(T))),
  finish(start+n), end_storage(start+n)
{
	for (T* it=start;it!=finish;++it) new (it) T(val);
} 

// dtor
template<typename T>
vector<T>::~vector() 
{ 
	for (T* it=start;it!=finish;++it) it->~T();
  	operator delete[](start); 
}

// copy ctor
template<typename T>
vector<T>::vector(const vector<T>& rhs)
: start(0), finish(0), end_storage(0)  
{
  	if (!rhs.empty()) {
		start=(T*)operator new[](rhs.capacity()*sizeof(T));
		finish=start+rhs.size();
		end_storage=start+rhs.capacity();
		for (size_type i=0;i<rhs.size();i++) 
			new (start+i) T(rhs.start[i]);
  	} 
}

// capacity
template<typename T>
typename vector<T>::size_type vector<T>::size() const { return finish-start; }

template<typename T>
typename vector<T>::size_type vector<T>::capacity() const { return end_storage-start; }

template<typename T>
bool vector<T>::empty() const { return size()==0; }

// element access
template<typename T>
typename vector<T>::reference vector<T>::operator[](size_type n) { return start[n]; } 

template<typename T>
typename vector<T>::const_reference vector<T>::operator[](size_type n) const { return start[n]; }

// modifiers
template<typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,const T& val)
{
	if (capacity()==size()) {
		size_type n=capacity()==0?1:2*capacity();
		T* first=(T*)operator new[](n*sizeof(T));
		for (iterator it=begin();it!=pos;it++) new (first+(it-start)) T(*it);
		iterator new_pos=first+(pos-start);
		new (first+(pos-start)) T(val);
		for (iterator it=pos;it!=end();it++) new (first+(it-start)+1) T(*it);
		size_type sz=size();
  		this->~vector();
  		start=first;
  		finish=start+sz+1;
		end_storage=start+n;
		return new_pos;
	} else {
		if (pos==end()) new (finish) T(val);
		else {
			new (finish) T(*(finish-1)); 
			for (iterator it=finish-1;it!=pos;it--) *it=*(it-1);
			*pos=val;
		}
		finish++;
		return pos;
	}
}

template<typename T>
typename vector<T>::iterator vector<T>::erase(iterator pos)
{
	for (iterator it=pos+1;it!=end();it++) *(it-1)=*it;
	(--finish)->~T();
	return pos;
}

// operator+=
template<class T>
typename vector<T>& vector<T>::operator+=(const vector<T>& rhs)
{
	size_type sz=size()+rhs.size();
	if (capacity()<sz) {
		T *old_start=start,*old_finish=finish;
		size_type cap=1;
		while (cap<sz) cap<<=1;
		start=(T*)operator new(cap*sizeof(T));
		end_storage=start+cap;
		finish=start;
		for (T* it=old_start;it!=old_finish;++it) new (finish++) T(*it);
		for (T* it=old_finish;it!=old_start;) (--it)->~T(); 
		operator delete[](old_start);
	}
	T* rhs_finish=rhs.finish;
	for (T* it=rhs.start;it!=rhs_finish;++it) 
		new (finish++) T(*it);
	return *this;
}

