// WAP in C++ to generate the Fibonacci series upto n terms

#include<iostream>
using namespace std;

int main(){
    int n;
    cout<<"\n\tEnter the number of terms: ";
    cin>>n;
    int a=0, b=1, c;
    cout<<"\n\tFibonacci series upto "<<n<<" terms is: ";
    cout<<a<<" "<<b<<" ";
    for(int i=2; i<n; i++){
        c = a+b;
        cout<<c<<" ";
        a = b;
        b = c;
    }
    return 0;
}