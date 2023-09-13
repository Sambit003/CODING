#include <iostream>
using namespace std;

class A {
    public:
    void func();
};

void A::func() {
    cout << "\n\tInside A::func()";
}

int main() {
    A a;
    a.func();
    return 0;
}