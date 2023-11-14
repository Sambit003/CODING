// WAP in C++ to find maximum of two numbers using inline function.

#include<iostream>
using namespace std;

inline int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int a, b;
    cout << "\tEnter two numbers: ";
    cin >> a >> b;
    cout << "\tMaximum is: " << max(a, b) << endl;
    return 0;
}