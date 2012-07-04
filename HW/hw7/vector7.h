#include <initializer_list>
using namespace std;

template<typename T>
class vector {
public:
// types
   typedef size_t   size_type;
   typedef       T& reference;
   typedef const T& const_reference;
   typedef       T* iterator;
   typedef const T* const_iterator;

// ctor/copy ctor/dtor
    vector();
    explicit vector (size_type);                // C++11
         vector (size_type, const T&);          // C++11

// explicit vector (size_type,const T& = T());  // C++03
         vector (const vector& );
         vector (      vector&&);

         vector   & operator= (const vector&);
         vector<T>& operator= (      vector<T>&&);

         vector (initializer_list<T>);
             ~vector();
// iterators

          iterator begin  (void)       { return start;  }
    const_iterator begin  (void) const { return start;  }
    const_iterator cbegin (void) const { return start;  }       // C++11
          iterator end    (void)       { return finish; }
    const_iterator end    (void) const { return finish; }
    const_iterator cend   (void) const { return finish; }       // C++11

// modifiers
    // iterator insert (iterator,const T&);                     // C++03
    iterator insert (const_iterator,const T&);                  // C++11
    iterator insert (const_iterator,     T&&);

    // iterator erase (iterator);                               // C++03
    iterator erase (const_iterator);                            // C++11

    void push_back (const T& val) {insert(cend(), val);            }
    void push_back (     T&& val) {insert(cend(), std::move(val)); }

    void pop_back (void) { erase(cend()-1); }

    // capacity
    size_type     size (void) const { return finish - start;      }
    size_type capacity (void) const { return end_storage - start; }
    bool         empty (void) const { return size() == 0;         }

    // element access
          reference operator[] (size_type n)       { return start[n]; }
    const_reference operator[] (size_type n) const { return start[n]; }

      reference back()       { return *(end()-1); }
    const_reference back() const { return *(end()-1); }


private:
T *start, *finish, *end_storage;
};


template <typename T>
vector<T>::vector (void) : 
    start(NULL), finish(NULL), end_storage(NULL) { }


template <typename T>
vector<T>::vector (size_type n) : 
    start((T*)operator new [] (sizeof(T) * n)),
    finish(start + n), end_storage(start + n) {

    for (iterator i = begin(); i != end(); i++)
        new (i) T();                   // using default value of T

}


template <typename T>
vector<T>::vector (size_type n, const T& val) : 
    start((T*)operator new [] (sizeof(T) * n)),
    finish(start + n), end_storage(start + n) {

    for (iterator i = begin(); i != end(); i++)
        new (i) T(val);

}


template <typename T>
vector<T>::vector (const vector &rhs) : 
    start((T*)operator new [] (sizeof(T) * rhs.size())),
    finish(start + rhs.size()),
    end_storage(start + rhs.capacity()) {

    for (iterator i = begin(); i != end(); i++)
        new (i) T(rhs[i - cbegin()]);

}


template <typename T>
vector<T>::vector (vector &&rhs) : 
    start(rhs.begin()),
    finish(start + rhs.size()), 
    end_storage(start + rhs.capacity()) {

    rhs.start       = NULL;
    rhs.finish      = NULL;
    rhs.end_storage = NULL;

}


template <typename T>
vector<T>& vector<T>::operator= (const vector& rhs) {
    if (capacity() < rhs.size()) {
        // need more space for our vecotr
        // destroy itself
        for (iterator i = begin(); i != end(); i++)
            i->~T();
        operator delete [] (start);

        // get more space and copy the old vector to it
        start       = static_cast<T *>(operator new [] (sizeof(T) * rhs.capacity()));
        finish      = start + rhs.size();
        end_storage = start + rhs.capacity();

        for (iterator i = begin(); i != end(); i++)
            new (i) T(rhs[i - cbegin()]);

    }
    else {
        int n = 0;
        iterator i;
        if (size() <= rhs.size()) {
            for (i = begin(); i != end(); i++, n++)
                new (i) T(rhs[i - cbegin()]);

            for (; n < rhs.size(); i++, n++)
                new (i) T(rhs[n]);
        }
        else {
            for (i = begin(); n < rhs.size(); i++, n++)
                new (i) T(rhs[i - cbegin()]);

            for (; i != end(); i++)
                i->~T();
        }
    }
}


template <typename T>
vector<T>& vector<T>::operator= (vector<T>&& rhs) {
    // just destroy itself and move the pointers
    for (iterator i = begin(); i != end(); i++)
        i->~T();
    operator delete [] (start);

    start       = rhs.begin();
    finish      = start + rhs.size();
    end_storage = start + rhs.capacity();

    rhs.start       = NULL;
    rhs.finish      = NULL;
    rhs.end_storage = NULL;

    return *this;
}


// fucking C++11 list-initialization Orz
template <typename T>
vector<T>::vector (initializer_list<T> init) :
    start(static_cast<T *>(operator new [] (sizeof(T) * init.size()))),
    finish(start), end_storage(start + init.size()) {
    // evil C++11 range-based for
    for (auto &x : init)
        push_back(x);
}


template <typename T>
vector<T>::~vector (void) {
    for (iterator i = begin(); i != end(); i++)
        i->~T();
    operator delete [] (start);
}


template <typename T>
typename vector<T>::iterator
vector<T>::insert (const_iterator pos, const T& val) {
    // current capacity
    size_type c = capacity();
    iterator i;
    // need more space
    if (c == size()) {
        T *new_this, *p, *rt;
        c = c == 0 ? 1 : 2 * c;      // doubled the capacity
        p = new_this = static_cast<T *>(operator new [] (sizeof(T) * c));

        // move old data to the new space
        for (i = begin(); i != pos; i++, p++)
            new (p) T(std::move(*i));

        new (p) T(val);        // insert the value

        rt = p;                // return this
        p++;

        // continue to move old data
        for (; i != end(); i++, p++)
            new (p) T(std::move(*i));

        // goodbye, my old vector
        for (i = begin(); i != end(); i++)
            i->~T();
        operator delete [] (start);

        start = new_this;
        finish = p;
        end_storage = start + c;
        return rt;
    }
    else {
        for (i = end(); i != pos; i--)
            new (i) T(std::move(*(i-1)));
        new (i) T(val);

        finish++;
        return i;
    }
}


template <typename T>
typename vector<T>::iterator
vector<T>::insert (const_iterator pos, T&& val) {
    size_type c = capacity();
    iterator i;
    if (c == size()) {
        T *new_this, *p, *rt;
        c = c == 0 ? 1 : 2 * c;
        p = new_this = static_cast<T *>(operator new [] (sizeof(T) * c));
        for (i = begin(); i != pos; i++, p++)
            new (p) T(std::move(*i));

        new (p) T(std::move(val));        // using move ctor
        rt = p;
        p++;

        for (; i != end(); i++, p++)
            new (p) T(std::move(*i));

        for (i = begin(); i != end(); i++)
            i->~T();
        operator delete [] (start);

        start = new_this;
        finish = p;
        end_storage = start + c;
        return rt;
    }
    else {
        for (i = end(); i != pos; i--)
            new (i) T(std::move(*(i-1)));
        new (i) T(std::move(val));

        finish++;
        return i;
    }
}


template <typename T>
typename vector<T>::iterator vector<T>::erase (const_iterator pos) {
    iterator i;
    pos->~T();
    for (i = const_cast<iterator>(pos+1); i != end(); i++)
        *(i-1) = (std::move(*(i)));

    finish--;
    if (empty())
        return end();

    return const_cast<iterator>(pos);
}

