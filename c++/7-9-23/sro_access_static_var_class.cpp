#include <iostream>
using namespace std;

class A {
    public:
    static int x;
    static int y;
    void func(int x){
        cout << "\n\tStatic variable x = " << A::x << endl;
        cout << "\tStatic variable y = " << A::y << endl;
    }
};

int A::x = 10;
int A::y = 20;

int main() {
    A a;
    int x = 30;
    a.func(x);
    cout << "\n\tThe value of y [accessing from main function]: " << A::y << endl;
    return 0;
}