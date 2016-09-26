#ifndef VECTOR_H
#define VECTOR_H

#include "vexception.h"
#include <iostream>

template<typename T>
class Vector
{
    T* ptr;
    size_t _size;
public:
    Vector() throw(VException);
    explicit Vector(size_t) throw( VException );
    Vector(std::initializer_list<T>) throw( VException );
    Vector(const Vector&) throw( VException );
    ~Vector();

    T&                      front();
    T&                      back();

    bool                    empty();

    void                    clear() throw( VException );

    int                     size();

    T&                      at(size_t) throw( VException );

    void                    push_back(T) throw( VException );
    void                    push_front(T) throw( VException );
    void                    pop_back() throw( VException );
    void                    pop_front() throw( VException );

    void                    sort();


    T&                      operator [] (const size_t) throw( VException );

    template<typename T1>
    friend std::ostream&    operator << (std::ostream&, const Vector<T1>&);

    template<typename T1>
    friend std::istream&    operator >> (std::istream&, const Vector<T1>&);

    Vector<T>               operator = (const Vector<T>&) throw( VException );

    Vector<T>               operator + (const Vector<T>&);
    Vector<T>               operator - (const Vector<T>&);
};

template<typename T>
Vector<T>::Vector() throw( VException )
    :_size(0)
{
    try
    {
        ptr = new T;
    }
    catch(std::bad_alloc& ba)
    {
        throw VException("Bad alloc");
    }
}

template<typename T>
Vector<T>::Vector(size_t aSize) throw( VException )
    :_size(aSize)
{
    try
    {
        ptr = new T[aSize];
    }
    catch(std::bad_alloc& ba)
    {
        throw VException("Bad alloc");
    }

    for(size_t i = 0; i < aSize; i++)
    {
        ptr[i]=0;
    }
}

template<typename T>
Vector<T>::Vector(std::initializer_list<T> il) throw( VException )
    :_size(il.size())
{
    try
    {
        ptr = new T[il.size()];
    }
    catch(std::bad_alloc& ba)
    {
        throw VException("Bad alloc");
    }

    typename std::initializer_list<T>::iterator it = il.begin();

    for(size_t i = 0; i < _size && it != il.end(); i++)
    {
        ptr[i] = *it;
        it++;
    }
}

template<typename T>
Vector<T>::Vector(const Vector& v) throw( VException )
    :_size(v._size)
{
    try
    {
        ptr = new T[v._size];
    }
    catch(std::bad_alloc& ba)
    {
        throw VException("Bad alloc");
    }

    for(size_t i = 0; i < v._size; i++)
    {
        ptr[i]=v.ptr[i];
    }
}

template<typename T>
Vector<T>::~Vector()
{
    _size = 0;
    delete[] ptr;
    ptr = nullptr;
}

template<typename T>
T& Vector<T>::front()
{
    return *ptr;
}

template<typename T>
T& Vector<T>::back()
{
    return ptr[_size-1];
}

template<typename T>
bool Vector<T>::empty()
{
    if(_size == 0)
    {
        return true;
    }
    return false;
}

template<typename T>
void Vector<T>::clear() throw( VException )
{
    _size = 0;
    if(ptr != nullptr) delete[] ptr;
    try
    {
        ptr = new T;
    }
    catch(VException& ex)
    {
        throw("Bad alloc");
    }
}

template<typename T>
int Vector<T>::size()
{
    return _size;
}

template<typename T>
T& Vector<T>::at(size_t index) throw( VException )
{
    if(index >= _size)
    {
        throw VException("Incorrect index");
    }

    return ptr[index];
}

template<typename T>
void Vector<T>::push_back(T value) throw( VException )
{
    try
    {
        T* v = new T[++_size];

        for(size_t i = 0; i < _size; i++) // перенос всех элементов этого вектора в новый
        {
            v[i] = ptr[i];
        }
        v[_size-1] = value; // инициализация последнего элемента нового вектора переданным значением

        delete[] ptr;

        ptr = v;

        v = nullptr;
    }
    catch(std::bad_alloc& ba)
    {
        throw VException("Bad alloc");
    }
}

template<typename T>
void Vector<T>::push_front(T value) throw( VException )
{
    try
    {
        T* v = new T[++_size];

        v[0] = value; // инициализация 0 элемента нового вектора переданным значением
        for(size_t i = 1; i < _size+1; i++) // перенос всех элементов этого вектора в новый, начиная с 1 элемента
        {
            v[i] = ptr[i-1];
        }

        delete[] ptr;

        ptr = v;

        v = nullptr;
    }
    catch(std::bad_alloc& ba)
    {
        throw VException("Bad alloc");
    }
}

template<typename T>
void Vector<T>::pop_back() throw( VException )
{
    if(empty())
    {
        throw VException("Deleting element from empty vector");
    }

    try
    {
        T* tempV = new T[--_size];

        for(size_t i = 0; i < _size; i++) // перенос элементов этого вектора кроме последнего в новый
        {
            tempV[i] = ptr[i];
        }

        delete[] ptr;

        ptr = tempV;

        tempV = nullptr;
    }
    catch(std::bad_alloc& ba)
    {
        throw VException("Bad alloc");
    }
}

template<typename T>
void Vector<T>::pop_front() throw( VException )
{
    if(empty())
    {
        throw VException("Deleting element from empty vector");
    }

    try
    {
        T* tempV = new T[--_size];

        for(size_t i = 1; i < _size+1; i++) // перенос элементов этого вектора кроме первого в новый
        {
            tempV[i-1] = ptr[i];
        }

        delete[] ptr;

        ptr = tempV;

        tempV = nullptr;
    }
    catch(std::bad_alloc& ba)
    {
        throw VException("Bad alloc");
    }
}

template<typename T>
void Vector<T>::sort()
{
    //Выбором
    for(size_t i = 0; i < _size-1; i++)
    {
        size_t min_index = i;
        for(size_t j = min_index+1; j < _size; j++)
        {
            if(ptr[min_index] > ptr[j])
            {
                min_index = j;
            }
        }

        if(min_index != i)
        {
            size_t temp = ptr[i];
            ptr[i] = ptr[min_index];
            ptr[min_index] = temp;
        }
    }
}

template<typename T>
T& Vector<T>::operator [] (const size_t i) throw( VException )
{
    if(i >= _size)
    {
        throw VException("Incorrect index");
    }

    return ptr[i];
}

template<typename T>
std::ostream& operator << (std::ostream& os, const Vector<T>& v)
{
    for(size_t i = 0; i < v._size; i++)
    {
        os << v.ptr[i] << " ";
    }
    return os;
}

template<typename T>
std::istream& operator >> (std::istream& is, const Vector<T>& v)
{
    for(size_t i = 0; i < v._size; i++)
    {
        is >> v.ptr[i];
    }
    return is;
}

template<typename T>
Vector<T>  Vector<T>::operator = (const Vector<T> & other) throw( VException )
{
    try
    {
        if(ptr != nullptr)
        {
            delete[] ptr;
        }
        _size = other._size;
        ptr = new T[_size];

        for(size_t i = 0; i < _size; i++)
        {
            ptr[i] = other.ptr[i];
        }

        return *this;
    }
    catch(std::bad_alloc& ba)
    {
        throw VException("Bad alloc");
    }
}

template<typename T>
Vector<T> Vector<T>::operator + (const Vector<T>& v)
{
    size_t __size = _size > v._size ? _size : v._size;
    size_t min_size = _size < v._size ? _size : v._size;

    Vector<T> tempV(__size);

    for(size_t i = 0; i < __size; i++)
    {
        if(i < min_size)
        {
            tempV.ptr[i] = ptr[i] + v.ptr[i];
        }
        else
        {
            tempV.ptr[i] = ptr[i];
        }
    }

    return tempV;
}

template<typename T>
Vector<T> Vector<T>::operator - (const Vector<T>& v)
{
    size_t __size = _size > v._size ? _size : v._size;
    size_t min_size = _size < v._size ? _size : v._size;

    Vector<T> tempV(__size);

    for(size_t i = 0; i < __size; i++)
    {
        if(i < min_size)
        {
            tempV.ptr[i] = ptr[i] - v.ptr[i];
        }
        else
        {
            tempV.ptr[i] = ptr[i];
        }
    }

    return tempV;
}

#endif // VECTOR_H
