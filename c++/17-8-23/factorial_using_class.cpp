// WAP in C++ to find factorial of a number using class.

#include<iostream>
using namespace std;

class factorial
{
    int n;
public:
    void getdata()
    {
        cout<<"\n\t Enter a number: ";
        cin>>n;
    }
    void fact()
    {
        int i,f=1;
        for(i=1;i<=n;i++)
            f=f*i;
        cout<<"\n\t Factorial of "<<n<<" is "<<f;
    }
};

int main()
{
    factorial f;
    f.getdata();
    f.fact();
    return 0;
}