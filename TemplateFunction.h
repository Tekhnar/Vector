#ifndef TEMPLATEFUNCTION_H_INCLUDED
#define TEMPLATEFUNCTION_H_INCLUDED



//-------------------start of constructor and destructor------------------

template <class T>
Vector<T>::Vector ():
    data_ ( (T*) calloc (DEFAULT_CAPACITY, sizeof (T)) ),
    size_ (0),
    capacity_ (DEFAULT_CAPACITY)
{}


template <class T>
Vector<T>::Vector (const T& value):
    data_ ( (T*) calloc (DEFAULT_CAPACITY, sizeof (T)) ),
    size_ (0),
    capacity_ (DEFAULT_CAPACITY)
{
    this->push_back(value);
}

template <class T>
Vector<T>::Vector (const Vector& that):
    data_ ( (T*) calloc (that.capacity_, sizeof (T)) ),
    size_ (that.size_),
    capacity_ (that.capacity_)
{
    for (size_t i = 0; i < size_; i++) {
        this->data_[i] = that.data_[i];
    }
}


template <class T>
Vector<T>::~Vector () {
    for (size_t i = 0; i < size_; i++) {
        data_[i].~T();
    }
    free (data_);
}

//---------------------end of constructor and destructor------------------


template <class T>
void Vector<T>::autoIncreaseLength () {
    if (size_ >= capacity_) {
        T* temp_point = (T*) realloc ((void*) data_, capacity_ * INCREASE_FACTOR * sizeof (T));
        if (temp_point != nullptr) {
                printf ("----");
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
    if (std::is_class<T>::value == true)
        new ((void*)(data_ + size_)) T;
//        std::allocator<T>::construct ((data_ + size_), &temp);
    data_[size_] = value;
    size_++;
}


template <class T>
T Vector<T>::pop_back () {
    if (size_ <= 0) {
        printf ("Vector is empty!\n");
        return 0;
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
#endif // TEMPLATEFUNCTION_H_INCLUDED
