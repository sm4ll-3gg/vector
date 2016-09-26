#include <iostream>
#include "vector.h"
int main()
{
    int n;
    std::cout<<"Введите размер вектора"<<std::endl;
    std::cin>>n;

    Vector<int> v(n);

    std::cout<<"Введите значения n элементов вектора"<<std::endl;
    std::cin >> v; // Инициализируем вектор значениями

    std::cout<<"\nВведенный вектор: "<<v<<std::endl;
    std::cout<<"Певый элемент = "<<v.front()
            <<"\nПоследний элемент = "<<v.back()
           <<"\nРазмер = "<<v.size()<<std::endl;

    v.sort(); // Сортировка методом выбора
    std::cout<<"\nВектор после сортировки: "<<v<<std::endl;

    try
    {
        v.pop_back();
        std::cout<<"\nВектор после удаления последнего элемента: "<<v<<std::endl;
        v.pop_front();
        std::cout<<"Первого: "<<v<<std::endl;

        std::cout<<"\nВведите число."<<std::endl;
        std::cin>>n;
        v.push_back(n);
        std::cout<<"Введенное число добавлено в конец вектора: "<<v<<std::endl;
        v.push_front(n);
        std::cout<<"И в начало: "<<v<<std::endl;
    }
    catch(VException& ex)
    {
        std::cout << ex.get_name() << std::endl;
    }

    Vector<int> v1;
    std::cout<<"\nСоздан пустой вектор.\n"<<"v1.empty() = "<<v1.empty()<<std::endl;

    try
    {
        v1.push_back(5);
        v1.push_front(2);
    }
    catch(VException& ex)
    {
        std::cout << ex.get_name() << std::endl;
    }

    std::cout<<"Сначала в конец добавлено число 5, а затем в начало 2: "<<v1<<std::endl;

    try
    {
        Vector<int> v2 = v+v1;
        std::cout<<"\nСоздан вектор v2 = v + v1: "<<v2<<std::endl;

        v2 = v2 - v1;
        std::cout<<"v2 = v2 - v1 : "<<v2<<std::endl;

        std::cout << "v1.clear()" << std::endl;
        v1.clear();
        std::cout << "v1 = " << v1 << std::endl;
        v2 = v2 - v1;
        std::cout << "v2 = v2 - v1 : " << v2 << std::endl;
    }
    catch(VException& ex)
    {
        std::cout << ex.get_name() << std::endl;
    }

    Vector<int>* vp;
    try
    {
        std::cout << "\nПопытка выделения памяти под пустой Vector<int>..." << std::endl;
        vp = new Vector<int>;
    }
    catch(VException& ex)
    {
        std::cout << "Произошла ошибка при выделении памяти.\nСообщение от обработчика: "
                  << ex.get_name() << std::endl;
    }

    try
    {
        std::cout << "\nПопытка удаления последнего элемента вектора..." << std::endl;
        vp->pop_back();
    }
    catch(VException& ex)
    {
        std::cout << "Произошла ошибка при удалении элемента.\nСообщение от обработчика: "
                  << ex.get_name() << std::endl;
    }

    try
    {
        std::cout << "\nПопытка добавления числа 8 в конец вектора..." << std::endl;
        vp->push_back(8);
    }
    catch(VException& ex)
    {
        std::cout << "Произошла ошибка при добавлении элемента.\nСообщение от обработчика: "
                  << ex.get_name() << std::endl;
    }
    std::cout << "\nВектор vp = " << *vp << std::endl;

    try
    {
        std::cout << "\nПопытка получить доступ к 1-му элементу вектора..." << std::endl;
        std::cout << "Первый элемент вектора = " << vp->at(1) << std::endl;
    }
    catch(VException& ex)
    {
        std::cout << "Произошла ошибка при получении доступа к элементу.\nСообщение от обработчика: "
                  << ex.get_name() << std::endl;
    }

    try
    {
        std::cout << "\nПопытка получить доступ к 1-му элементу вектора (operator [])..." << std::endl;
        std::cout << "Первый элемент вектора = " << (*vp)[1] << std::endl;
    }
    catch(VException& ex)
    {
        std::cout << "Произошла ошибка при получении доступа по индексу.\nСообщение от обработчика: "
                  << ex.get_name() << std::endl;
    }
}
