#include <iostream>
#include "vector.h"

using namespace std;

int main()
{
    int n;
    cout<<"Введите размер вектора"<<endl;
    cin>>n;

    Vector<int> v(n);

    cout<<"Введите значения n элементов вектора"<<endl;
    cin >> v; // Инициализируем вектор значениями

    cout<<"\nВведенный вектор: "<<v<<endl;
    cout<<"Певый элемент = "<<v.front()
        <<"\nПоследний элемент = "<<v.back()
        <<"\nРазмер = "<<v.size()<<endl;

    v.sort(); // Сортировка методом выбора
    cout<<"\nВектор после сортировки: "<<v<<endl;

    v.pop_back();
    cout<<"\nВектор после удаления последнего элемента: "<<v<<endl;
    v.pop_front();
    cout<<"Первого: "<<v<<endl;

    cout<<"\nВведите число."<<endl;
    cin>>n;
    v.push_back(n);
    cout<<"Введенное число добавлено в конец вектора: "<<v<<endl;
    v.push_front(n);
    cout<<"И в начало: "<<v<<endl;

    Vector<int> v1;
    cout<<"\nСоздан пустой вектор.\n"<<"v1.empty() = "<<v1.empty()<<endl;
    v1.push_back(5);
    v1.push_front(2);
    cout<<"Сначала в конец добавлено число 5, а затем в начало 2: "<<v1<<endl;

    Vector<int> v2 = v+v1;
    cout<<"\nСоздан вектор v2 = v + v1: "<<v2<<endl;

    v2 = v2 - v1;
    cout<<"Абстрактная операция '-' (v2 = v2 - v1): "<<v2<<endl;
}
