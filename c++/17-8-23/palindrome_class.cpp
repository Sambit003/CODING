// WAP in C++ to check whether a number is palindrome or not using class.

#include<iostream>
using namespace std;

class palindrome
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
        int temp=n,rev=0,rem;
        while(temp!=0)
        {
            rem=temp%10;
            rev=rev*10+rem;
            temp=temp/10;
        }
        if(rev==n)
            cout<<"\n\t "<<n<<" is a palindrome number.";
        else
            cout<<"\n\t "<<n<<" is not a palindrome number.";
    }
};

int main()
{
    palindrome p;
    p.getdata();
    p.check();
    return 0;
}