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

    Vector<int> v1;
    std::cout<<"\nСоздан пустой вектор.\n"<<"v1.empty() = "<<v1.empty()<<std::endl;
    v1.push_back(5);
    v1.push_front(2);
    std::cout<<"Сначала в конец добавлено число 5, а затем в начало 2: "<<v1<<std::endl;

    Vector<int> v2 = v+v1;
    std::cout<<"\nСоздан вектор v2 = v + v1: "<<v2<<std::endl;

    v2 = v2 - v1;
    std::cout<<"Абстрактная операция '-' (v2 = v2 - v1): "<<v2<<std::endl;
}
