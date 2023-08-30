// WAP in C++ to find fibonacci series using class. 

#include<iostream>
using namespace std;

class fibonacci
{
    int n;
public:
    void getdata()
    {
        cout<<"\n\t Enter a number: ";
        cin>>n;
    }
    void generate_fib()
    {
        int a=0,b=1,c,i;
        cout<<"\n\t Fibonacci series upto "<<n<<" terms is: ";
        cout<<a<<" "<<b<<" ";
        for(i=1;i<=n-2;i++)
        {
            c=a+b;
            cout<<c<<" ";
            a=b;
            b=c;
        }
    }
};

int main()
{
    fibonacci f;
    f.getdata();
    f.generate_fib();
    return 0;
}