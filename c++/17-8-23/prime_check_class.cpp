// WAP in C++ to check whether a number is prime or not using class.

#include<iostream>
using namespace std;

class prime
{
    int n;
public:
    void getdata()
    {
        cout<<"\n\t Enter a number: ";
        cin>>n;
    }
    void check()
    {
        int i,flag=0;
        for(i=2;i<n;i++)
        {
            if(n%i==0)
            {
                flag=1;
                break;
            }
        }
        if(flag==0)
            cout<<n<<" is a prime number.";
        else
            cout<<n<<" is not a prime number.";
    }
};

int main()
{
    prime p;
    p.getdata();
    p.check();
    return 0;
}