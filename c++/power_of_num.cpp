// WAP in C++ to find the power of a number

#include<iostream>
using namespace std;

int main(){
    int pow, num;
    cout<<"\n\tEnter a number: ";
    cin>>num;
    cout<<"\n\tEnter the power: ";
    cin>>pow;

    int res = 1;
    for(int i=1; i<=pow; i++){
        res *= num;
    }

    cout<<"\n\t"<<num<<" raised to the power "<<pow<<" is "<<res;
    return 0;
}