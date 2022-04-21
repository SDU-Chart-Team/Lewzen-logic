//
// Created by l'l on 2022/3/19.
//


#include<bits/stdc++.h>
using namespace std;
class Base
{
public:
    virtual void func()
    {
        cout << "Base!" << endl;
    }
};
class Derived :public Base
{
public:

};

void show(Base& b)
{
    b.func();
}
Base base;
Derived derived;

//int main()
//{
//    Base*  a =  new Derived();
//    a->func();
//
//    return 0;
//}
