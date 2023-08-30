// WAP in C++ to find the factorial of a number

#include<iostream>
using namespace std;

int main(){
    int n;
    cout<<"\n\tEnter a number: ";
    cin>>n;
    int fact=1;
    for(int i=1; i<=n; i++){
        fact *= i;
    }
    cout<<"\n\tFactorial of "<<n<<" is "<<fact;
    return 0;
}