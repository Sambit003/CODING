// WAP IN C++ TO CHECK WHETHER A NUMBER IS PRIME OR NOT

#include<iostream>
using namespace std;

int main(){
    int n;
    cout<<"\n\tEnter a number: ";
    cin>>n;
    int i;
    for(i=2; i<n; i++){
        if(n%i==0){
            cout<<"\n\t"<<n<<" is not a prime number";
            break;
        }
    }
    if(i==n){
        cout<<"\n\t"<<n<<" is a prime number";
    }
    return 0;
}