/*
    Friend is a keyword which is used to access private and protected
    data members outside the class.

    Write a simple program in support of the above statement.
*/

#include<iostream>
using namespace std;

class addition{
    private:
        int a, b;
    public:
        addition(){
            a = 10;   b = 20;
            cout << "\n\tReceived: " << a << ", " << b << endl;
        }
        friend int add(addition);
};

int add(addition a){
    return a.a + a.b;
}

int main(){
    addition a;
    cout << "\tSum: "<< add(a) << endl;
}
