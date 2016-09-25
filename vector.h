#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

template<typename T>
class Vector
{
    T* ptr;
    size_t _size;
public:
    Vector();
    explicit Vector(size_t);
    Vector(const Vector&);
    ~Vector();

    T&                      front();
    T&                      back();

    bool                    empty();

    int                     size();

    T&                      at(size_t);

    void                    push_back(T);
    void                    push_front(T);
    void                    pop_back();
    void                    pop_front();

    void                    sort();


    T&                      operator [] (const size_t);

    template<typename T1>
    friend std::ostream&    operator << (std::ostream&, const Vector<T1>&);

    template<typename T1>
    friend std::istream&    operator >> (std::istream&, const Vector<T1>&);

    Vector<T>               operator = (const Vector<T>&);

    Vector<T>               operator + (const Vector<T>&);
    Vector<T>               operator - (const Vector<T>&);
};

template<typename T>
Vector<T>::Vector()
    :_size(0)
{
    ptr = new T;
}

template<typename T>
Vector<T>::Vector(size_t aSize)
    :_size(aSize)
{
    ptr = new T[aSize];

    for(size_t i = 0; i < aSize; i++)
    {
        ptr[i]=0;
    }
}

template<typename T>
Vector<T>::Vector(const Vector& v)
    :_size(v._size)
{
    ptr = new T[v._size];
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
int Vector<T>::size()
{
    return _size;
}

template<typename T>
T& Vector<T>::at(size_t index)
{
    if(index<_size && index>=0)
    {
        return ptr[index];
    }
    return *ptr; // тут должно выбрасываться исключение, но лень
}

template<typename T>
void Vector<T>::push_back(T value)
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

template<typename T>
void Vector<T>::push_front(T value)
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

template<typename T>
void Vector<T>::pop_back()
{
    if(empty())
    {
        return; // исключение
    }

    T* tempV = new T[--_size];

    for(size_t i = 0; i < _size; i++) // перенос элементов этого вектора кроме последнего в новый
    {
        tempV[i] = ptr[i];
    }

    delete[] ptr;

    ptr = tempV;

    tempV = nullptr;
}

template<typename T>
void Vector<T>::pop_front()
{
    if(empty())
    {
        return; // исключение
    }

    T* tempV = new T[--_size];

    for(size_t i = 1; i < _size+1; i++) // перенос элементов этого вектора кроме первого в новый
    {
        tempV[i-1] = ptr[i];
    }

    delete[] ptr;

    ptr = tempV;

    tempV = nullptr;
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
T& Vector<T>::operator [] (const size_t i)
{
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
Vector<T>  Vector<T>::operator = (const Vector<T> & other)
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
