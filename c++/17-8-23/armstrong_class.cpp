// WAP in C++ to check whether a number is armstrong or not using class.

#include<iostream>
#include<cmath>
using namespace std;

class armstrong
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
        int temp=n,rem,sum=0;
        while(temp!=0)
        {
            rem=temp%10;
            sum=sum+pow(rem,3);
            temp=temp/10;
        }
        if(sum==n)
            cout<<"\n\t "<<n<<" is an armstrong number.";
        else
            cout<<"\n\t "<<n<<" is not an armstrong number.";
    }
};

int main()
{
    armstrong a;
    a.getdata();
    a.check();
    return 0;
}