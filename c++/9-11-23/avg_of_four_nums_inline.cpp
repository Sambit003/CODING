// WAP in C++ to find average of four numbers using inline function.

#include<iostream>
using namespace std;

inline float avg(float a, float b, float c, float d) {
    return (a + b + c + d) / 4;
}

int main() {
    float a, b, c, d;
    cout << "\tEnter four numbers: ";
    cin >> a >> b >> c >> d;
    cout << "\tAverage: " << avg(a, b, c, d) << endl;
    return 0;
}