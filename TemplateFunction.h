#ifndef TEMPLATEFUNCTION_H_INCLUDED
#define TEMPLATEFUNCTION_H_INCLUDED

#define CHECK_CALLOC if (data_ == nullptr) \
    { \
        printf ("ERROR in calloc!\n");\
        exit (1); \
    }


//-------------------start of constructor and destructor------------------

template <class T>
Vector<T>::Vector ():
    data_ (0),
    size_ (0),
    capacity_ (0)
{
    Vector<T> temp(1);

    std::swap (temp.size_, this->size_);
    std::swap (temp.capacity_, this->capacity_);
    std::swap (temp.data_, this->data_);
}


template <class T>
Vector<T>::Vector (size_t size_default_alloc):
    data_ ( (T*) calloc (size_default_alloc, sizeof (T)) ),
    size_ (size_default_alloc),
    capacity_ (size_default_alloc)
{
    CHECK_CALLOC
    autoCallConstructor (data_, size_);
}

template <class T>
Vector<T>::Vector (const Vector& that):
    data_ ( (T*) calloc (that.capacity_, sizeof (T)) ),
    size_ (that.size_),
    capacity_ (that.capacity_)
{
    CHECK_CALLOC
    autoCallConstructor (data_, size_);

    for (size_t i = 0; i < size_; i++) {
        this->data_[i] = that.data_[i];
    }
}

template <class T>
Vector<T>::Vector (Vector&& that):
    data_ (0),
    size_ (0),
    capacity_ (0)
{
    if (&that != this) {
        std::swap (that.data_, this->data_);
        std::swap (that.size_, this->size_);
        std::swap (that.capacity_, this->capacity_);
    }
}

template <class T>
Vector<T>::~Vector () {
    for (size_t i = 0; i < size_; i++) {
        if (std::is_class<T>::value == true) {
            data_[i].~T();
        }
    }
    if (data_) {
        free (data_);
        data_ = 0;
    }
}

//---------------------end of constructor and destructor------------------


template <class T>
void Vector<T>::autoIncreaseLength () {
    if (size_ >= capacity_) {
        T* temp_point = (T*) realloc ((void*) data_, capacity_ * INCREASE_FACTOR * sizeof (T));
        if (temp_point != nullptr) {
            data_ = temp_point;
            capacity_ *= INCREASE_FACTOR;
        }
        else {
            printf ("ERROR in autoIncreaseLength() in realloc!\n New capacity = %lli\n", capacity_ * INCREASE_FACTOR);
            exit (1);
        }
    }
}


template <class T>
void Vector<T>::push_back (const T& value) {
    autoIncreaseLength ();
//    if (std::is_class<T>::value == true) {
//        printf ("is_class push_back\n");
//        new ((void*)(data_ + size_)) T;
//    }

    autoCallConstructor (data_, 1);

    data_[size_] = value;
    size_++;
}


template <class T>
T Vector<T>::pop_back () {
    if (size_ <= 0) {
        printf ("Vector is empty!\n");
        return;
    }
    else {
        return data_[--size_];
    }
}


template <class T>
void Vector<T>::dumpInt () {
    printf ("\n************DUMP-INT************\n");
    printf ("Point on Vector: [%p]\nSize = %llu\nCapacity = %llu\n{\n",
            this, size_, capacity_);
    for (size_t i = 0; i < capacity_; i++) {
        if (i < size_)
            printf ("   data[%2llu] = %d\n", i, data_[i]);
        else
            printf ("*  data[%2llu] = %d (NOT USE)\n", i, data_[i]);
    }
    printf ("}\n");
    printf ("************DUMP-INT************\n");
}


template <class T>
T& Vector<T>::operator[] (long long element_number) {
    return data_[element_number];
}


template <class T>
T& Vector<T>::at (size_t element_number) {
    if (element_number >= size_) {
        printf ("Invalid element index!\n");
        exit(1);
    }
    else
        return (*this)[element_number];
}

template <class T>
Vector<T>& Vector<T>::operator = (const Vector& that) {
    freeMemoryData ();
    data_ = (T*) calloc (that.capacity_, sizeof (T));
    this->size_     = that.size_;
    this->capacity_ = that.capacity_;

    for (size_t i = 0; i < size_; i++)
        this->data_[i] = that.data_[i];
    return *this;
}

template <class T>
void Vector<T>::freeMemoryData () {
    for (size_t i = 0; i < size_; i++) {
        data_[i].~T();
    }
    size_ = 0;
    capacity_ = 0;
    free (data_);
}

template <class T>
void Vector<T>::autoCallConstructor (T* pointer, size_t num_objects) {
    if (pointer == 0) {
        printf ("Error in autoCallConstructor: bad pointer!\n");
        return;
    }
    if (num_objects == 0) {
        printf ("Error in autoCallConstructor: bad number of objects!\n");
        return;
    }

    if (std::is_class<T>::value == true) {
        for (size_t i = 0; i < num_objects; i++) {
            new ((void*)(pointer + i)) T;
        }
    }
}
#endif // TEMPLATEFUNCTION_H_INCLUDED
