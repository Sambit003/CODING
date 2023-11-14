/*
    WAP in C++ to calculate the sum of the series:
    1^2 + 2^2 + 3^2 + ... + n^2
*/

#include<iostream>
using namespace std;

inline int result (int term){
    return (term*(term+1)*(2*term+1))/6;
}

int main(){
    int term;
    cout << "\tEnter the number of terms: ";
    cin >> term;
    cout << "\tSum of the series 1^2 + ... + " << term << "^2" << " is: " << result(term) << endl;
    return 0;
}