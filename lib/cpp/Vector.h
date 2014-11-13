#ifndef __VERCTOR_H__
#define __VERCTOR_H__

typedef int Rank;
#define DEFAULT_CAPACITY (1024)

template <typename T>
class Vector() {
protected:
    T* _elem;
    Rank _size;
    int _capacity;
    // copy from array v
    void copyFrom(T const* v, Rank lo, Rank hi) {
        _size = hi - lo;
        _capacity = _size << 1;
        _elem = new T[_capacity];
        for(; lo < hi; _elem[lo] = v[lo++]);
    }
public:
    // construct a vector with capacity c, size s, and initial value v to all elements
    Vector(int c = DEFAULT_CAPACITY, Rank s = 0, T v) {
        _elem = new T[_capacity = c];
        for(_size = 0; _size < s; _elem[_size++] = v);
    }
    
    // copy from an array
    Vector(T const* a, int n) {
        copyFrom(a, 0, n);
    }
    Vector(T const* a, int lo, int hi) {
        copyFrom(a, lo, hi);
    }
    
    // copy from a vector
    Vector(Vector<T> const& v) {
        copyFrom(v._elem, 0, v._size);
    }
    Vector(Vector<T> const& v, Rank lo, Rank hi) {
        copyFrom(v._elem, lo, hi);
    }
    
    ~Vector() {
        delete [] _elem;
    }
    
    int size() const {
        return _size;
    };
    
    bool empty() const {
        return !_size;
    }
};

#endif // __VERCTOR_H__
