#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

template<typename T>
class Vector
{
    T* ptr;
    int _size;
public:
    Vector();
    explicit Vector(int);
    Vector(const Vector&);
    ~Vector();

    T&                      front();
    T&                      back();

    bool                    empty();

    int                     size();

    T&                      at(int);

    void                    push_back(T);
    void                    push_front(T);
    void                    pop_back();
    void                    pop_front();

    void                    sort();


    T&                      operator[] (int);

    template<typename T1>
    friend std::ostream&    operator <<(std::ostream&, Vector<T1>&);

    template<typename T1>
    friend std::istream&    operator >>(std::istream&,Vector<T1>&);

    Vector<T>               operator = (const Vector<T>&);

    Vector<T>               operator+(Vector<T>&);
    Vector<T>               operator-(Vector<T>&);
};

template<typename T>
Vector<T>::Vector()
    :_size(0)
{
    ptr = new T;
}

template<typename T>
Vector<T>::Vector(int aSize)
    :_size(aSize)
{
    ptr = new T[aSize];

    for(int i=0;i<aSize;i++)
    {
        ptr[i]=0;
    }
}

template<typename T>
Vector<T>::Vector(const Vector& v)
    :_size(v._size)
{
    ptr = new T[v._size];
    for(int i(0);i<v._size;i++)
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
T& Vector<T>::at(int index)
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

    for(int i=0;i<_size;i++) // перенос всех элементов этого вектора в новый
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
    for(int i=1;i<_size+1;i++) // перенос всех элементов этого вектора в новый, начиная с 1 элемента
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

    T* v = new T[--_size];

    for(int i=0;i<_size;i++) // перенос элементов этого вектора кроме последнего в новый
    {
        v[i] = ptr[i];
    }

    delete[] ptr;

    ptr = v;

    v = nullptr;
}

template<typename T>
void Vector<T>::pop_front()
{
    if(empty())
    {
        return; // исключение
    }

    T* v = new T[--_size];

    for(int i=1;i<_size+1;i++) // перенос элементов этого вектора кроме первого в новый
    {
        v[i-1] = ptr[i];
    }

    delete[] ptr;

    ptr = v;

    v = nullptr;
}

template<typename T>
void Vector<T>::sort()
{
    //Выбором
    for(int i=0;i<this->_size-1;i++)
    {
        int min_index=i;
        for(int j=min_index+1;j<this->_size;j++)
        {
            if(ptr[min_index]>ptr[j])
            {
                min_index=j;
            }
        }

        if(min_index != i)
        {
            std::swap(ptr[i],ptr[min_index]);
        }
    }
}

template<typename T>
T& Vector<T>::operator[] (int i)
{
    return ptr[i];
}

template<typename T>
std::ostream& operator<<(std::ostream& os, Vector<T>& v)
{
    for(int i = 0; i < v.size();i++)
    {
        os<<v.at(i)<<" ";
    }
    return os;
}

template<typename T>
std::istream& operator>>(std::istream& is, Vector<T>& v)
{
    for(int i = 0; i < v.size(); i++)
    {
        is >> v.at(i);
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

    for(int i=0;i<_size;i++)
    {
        ptr[i] = other.ptr[i];
    }

    return *this;
}

template<typename T>
Vector<T> Vector<T>::operator +(Vector<T>& v)
{
    int __size = _size > v._size ? _size : v._size;
    int min_size = _size < v._size ? _size : v._size;

    Vector<T> tempV(__size);

    for(int i=0;i<__size;i++)
    {
        if(i<min_size)
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
Vector<T> Vector<T>::operator -(Vector<T>& v)
{
    int __size = _size > v._size ? _size : v._size;
    int min_size = _size < v._size ? _size : v._size;

    Vector<T> tempV(__size);

    for(int i=0;i<__size;i++)
    {
        if(i<min_size)
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
