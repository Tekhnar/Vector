#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <type_traits>
#include <cstdlib>
#include <new>
#include <algorithm>

template <class T>
struct Vector {
private:
    const size_t DEFAULT_CAPACITY = 5;
    const size_t INCREASE_FACTOR = 2;

public:
//-----------------------------------------------
    Vector ();
    Vector (size_t size_default_alloc);
    Vector (const Vector& that);
    Vector (Vector&& that);
    ~Vector ();

//-----------------------------------------------

    void push_back (const T& value);
    T pop_back ();

    size_t capacity () { return capacity_; };
    size_t size () { return size_; };

    Vector<T>& operator = (const Vector& that);
    T& operator [] (long long element_number);
    T& at (size_t element_number);

    void dumpInt ();

//-----------------------------------------------
private:
    T* data_;
    size_t size_;
    size_t max_size_;
    size_t capacity_;
    size_t number_of_first_element_;

    void autoCallConstructor (T* pointer, size_t num_objects);

    void autoIncreaseLength ();
    void freeMemoryData ();

};


//void* operator new (size_t, void* place) { printf ("NEW "); return (void*) place; };

//-------------------------------//
#include "TemplateFunction.h"
//-------------------------------//

#endif // VECTOR_H_INCLUDED
