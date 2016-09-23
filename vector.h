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
    Vector(int);
    T& front();
    T& back();
    bool empty();
    int size();
    T& at(int);
    void push_back(T);
    void push_front(T);
    void pop_back();
    void pop_front();
    void sort();
    T& operator[] (int);
    template<typename T1> friend std::ostream&  operator <<(std::ostream& os, Vector<T1>& v)
    {
        for(int i = 0; i < v.size();i++)
        {
            os<<v.at(i)<<" ";
        }
        return os;
    }
    template<typename T1> friend std::istream& operator >>(std::istream& is,Vector<T1> v)
    {
        for(int i = 0; i < v.size(); i++)
        {
            is >> v.at(i);
        }
        return is;
    }
    Vector<T> operator+(Vector<T>);
    Vector<T> operator-(Vector<T>);
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
    if(index<_size)
    {
        return ptr[index];
    }
    return *ptr; // тут должно выбрасываться исключение, но лень
}

template<typename T>
void Vector<T>::push_back(T value)
{
    Vector<T> v(_size+1);

    for(int i=0;i<this->size();i++) // перенос всех элементов этого вектора в новый
    {
        v.at(i) = this->ptr[i];
    }
    v.at(v.size()-1) = value; // инициализация последнего элемента нового вектора переданным значением

    delete[] this->ptr;

    this->ptr = v.ptr;
    this->_size = v._size;
}

template<typename T>
void Vector<T>::push_front(T value)
{
    Vector<T> v(_size+1);

    for(int i=1;i<this->size()+1;i++) // перенос всех элементов этого вектора в новый, начиная с 1 элемента
    {
        v.at(i) = this->ptr[i-1];
    }
    v.ptr[0] = value; // инициализация 0 элемента нового вектора переданным значением

    delete[] this->ptr;

    this->ptr = v.ptr;
    this->_size = v._size;
}

template<typename T>
void Vector<T>::pop_back()
{
    if(this->empty())
    {
        return; // исключение
    }

    Vector<T> v(_size-1);

    for(int i=0;i<_size-1;i++) // перенос элементов этого вектора кроме последнего в новый
    {
        v.at(i) = this->ptr[i];
    }

    delete[] this->ptr;

    this->ptr = v.ptr;
    this->_size = v._size;
}

template<typename T>
void Vector<T>::pop_front()
{
    if(this->empty())
    {
        return; // исключение
    }

    Vector<T> v(_size-1);

    for(int i=1;i<_size;i++) // перенос элементов этого вектора кроме первого в новый
    {
        v.at(i) = this->ptr[i];
    }

    delete[] this->ptr;

    this->ptr = v.ptr;
    this->_size = v._size;
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
Vector<T> Vector<T>::operator +(Vector<T> v)
{
    Vector<T> v1(this->_size + v._size);
    for(int i=0;i<this->_size;i++)
    {
        v1.at(i) = ptr[i];
    }
    for(int i=this->_size;i<v1.size();i++)
    {
        v1.at(i)=v.at(i-this->size());
    }

    return v1;
}

template<typename T>
Vector<T> Vector<T>::operator -(Vector<T> v)
{
    // Понятия не имею как должна работать бинарная опирация - для векторов)
    return v;
}

#endif // VECTOR_H
