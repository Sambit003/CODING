// WAP in C++ to find power of a number using class.

#include<iostream>
#include<cmath>
using namespace std;

class power
{
    int n,p;
public:
    void getdata()
    {
        cout<<"\n\t Enter a number: ";
        cin>>n;
        cout<<"\n\t Enter power: ";
        cin>>p;
    }
    void pow_calc()
    {
        cout << "\n\t " << n << " raised to the power " << p << " is " << pow(n,p);
    }
};

int main()
{
    power p;
    p.getdata();
    p.pow_calc();
    return 0;
}
