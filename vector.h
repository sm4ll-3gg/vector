#ifndef VECTOR_H
#define VECTOR_H

#include "vexception.h"
#include <iostream>

template<typename T>
class Vector
{
    T* ptr;
    size_t _size;

    size_t max_size;

    void                    free_resources() noexcept;
public:
    Vector() throw(VException);
    explicit Vector(size_t) throw( VException );
    Vector(std::initializer_list<T>) throw( VException );
    Vector(const Vector&) throw( VException );
    ~Vector() noexcept;

    T&                      front() const noexcept;
    T&                      back() const noexcept;

    bool                    empty() const noexcept;

    void                    clear() noexcept;

    const size_t&           size() const noexcept;

    T&                      at(size_t) const throw( VException );

    void                    push_back(T) throw( VException );
    void                    push_front(T) throw( VException );
    void                    pop_back() throw( VException );
    void                    pop_front() throw( VException );

    void                    sort() noexcept;


    T&                      operator [] (const size_t) const throw( VException );

    template<typename T1>
    friend std::ostream&    operator << (std::ostream&, const Vector<T1>&);

    template<typename T1>
    friend std::istream&    operator >> (std::istream&, const Vector<T1>&);

    const Vector<T>&        operator = (const Vector<T>&) throw( VException );

    Vector<T>               operator + (const Vector<T>&) noexcept;
    Vector<T>               operator - (const Vector<T>&) noexcept;
};

template<typename T>
void Vector<T>::free_resources() noexcept
{
    if(ptr != nullptr)
    {
        delete[] ptr;
    }
    _size = 0;
    max_size = 0;

    ptr = nullptr;
}

template<typename T>
Vector<T>::Vector() throw( VException )
    :_size(0), max_size(5)
{
    try
    {
        ptr = new T[5];
    }
    catch(std::bad_alloc& ba)
    {
        throw VException("Bad alloc");
    }
}

template<typename T>
Vector<T>::Vector(size_t aSize) throw( VException )
    :_size(aSize), max_size(aSize*2)
{
    try
    {
        ptr = new T[aSize*2];
    }
    catch(std::bad_alloc& ba)
    {
        throw VException("Bad alloc");
    }

    for(size_t i = 0; i < aSize*2; i++)
    {
        ptr[i]= T();
    }
}

template<typename T>
Vector<T>::Vector(std::initializer_list<T> il) throw( VException )
{
    try
    {
        free_resources();

        size_t temp = il.size();

        _size = temp;
        max_size = temp*2;

        ptr = new T[il.size()*2];
    }
    catch(std::bad_alloc& ba)
    {
        throw VException("Bad alloc");
    }

    typename std::initializer_list<T>::iterator it = il.begin();

    size_t i = 0;
    while(it != il.end())
    {
        ptr[i] = *it;
        i++;
        it++;
    }

    for(size_t i = il.size(); i < max_size; i++)
    {
        ptr[i] = T();
    }
}

template<typename T>
Vector<T>::Vector(const Vector& v) throw( VException )
{
    try
    {
        free_resources();

        _size = v._size;
        max_size = v.max_size;

        ptr = new T[v.max_size];
    }
    catch(std::bad_alloc& ba)
    {
        throw VException("Bad alloc");
    }

    for(size_t i = 0; i < v.max_size; i++)
    {
        ptr[i]=v.ptr[i];
    }
}

template<typename T>
Vector<T>::~Vector() noexcept
{
    free_resources();
}

template<typename T>
T& Vector<T>::front() const noexcept
{
    return *ptr;
}

template<typename T>
T& Vector<T>::back() const noexcept
{
    return ptr[_size-1];
}

template<typename T>
bool Vector<T>::empty() const noexcept
{
    if(_size == 0)
    {
        return true;
    }
    return false;
}

template<typename T>
void Vector<T>::clear() noexcept
{
    free_resources();
}

template<typename T>
const size_t& Vector<T>::size() const noexcept
{
    return _size;
}

template<typename T>
T& Vector<T>::at(size_t index) const throw( VException )
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
    if(_size == max_size)
    {
        //if(_size == 0 )
        try
        {
            T* v = new T[_size*2];

            for(size_t i = 0; i < _size; i++) // перенос всех элементов этого вектора в новый
            {
                v[i] = ptr[i];
            }
            v[_size] = value; // инициализация последнего элемента нового вектора переданным значением

            delete[] ptr;

            ptr = v;
            _size++;
            max_size *= 2;

            v = nullptr;
        }
        catch(std::bad_alloc& ba)
        {
            throw VException("Bad alloc");
        }
    }
    else
    {
        ptr[_size] = value;
        _size++;
    }
}

template<typename T>
void Vector<T>::push_front(T value) throw( VException )
{
    if(_size == max_size)
    {
        try
        {
            T* v = new T[_size*2];

            v[0] = value;
            for(size_t i = 1; i < _size+1; i++) // перенос всех элементов этого вектора в новый
            {
                v[i] = ptr[i-1];
            }

            delete[] ptr;

            ptr = v;
            _size++;
            max_size *= 2;

            v = nullptr;
        }
        catch(std::bad_alloc& ba)
        {
            throw VException("Bad alloc");
        }
    }
    else
    {
        for(size_t i = _size; i > 0; i--)
        {
            ptr[i] = ptr[i-1];
        }
        ptr[0] = value;

        _size++;
    }

}

template<typename T>
void Vector<T>::pop_back() throw( VException )
{
    if(empty())
    {
        throw VException("Deleting element from empty vector");
    }

    ptr[_size-1] = T();
    _size--;
}

template<typename T>
void Vector<T>::pop_front() throw( VException )
{
    if(empty())
    {
        throw VException("Deleting element from empty vector");
    }

    for(size_t i = 0; i < _size; i++)
    {
        ptr[i] = ptr[i+1];
    }

    _size--;
}

template<typename T>
void Vector<T>::sort() noexcept
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
T& Vector<T>::operator [] (const size_t i) const throw( VException )
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
const Vector<T>&  Vector<T>::operator = (const Vector<T> & other) throw( VException )
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
Vector<T> Vector<T>::operator + (const Vector<T>& v) noexcept
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
Vector<T> Vector<T>::operator - (const Vector<T>& v) noexcept
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
