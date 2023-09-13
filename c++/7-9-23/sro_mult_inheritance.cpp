#include <iostream>
using namespace std;

class A{
    public:
    int x;
    A(){ x= 10; }
};

class B{
    public:
    int x;
    B(){ x= 20; }
};

class C: public A, public B{
    public:
    void func(){
        cout << "\n\tThe value of x in class A: " << A::x << endl;
        cout << "\tThe value of x in class B: " << B::x << endl;
    }
};

int main(){
    C c;
    c.func();
    return 0;
}