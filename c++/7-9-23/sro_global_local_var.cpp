#include <iostream>
using namespace std;

int x = 10; // global variable

int main() {
    int x = 20; // local variable with same name as global variable
    cout << "\n\tLocal variable x = " << x << endl;
    cout << "\tGlobal variable x = " << ::x; // using scope resolution operator to access global variable
    return 0;
}
