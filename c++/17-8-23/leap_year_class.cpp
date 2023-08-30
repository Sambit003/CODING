// WAP in C++ to check whether a year is leap year or not using class.

#include<iostream>
using namespace std;

class leap_year {
    int y;
public:
    void getdata() {
        cout<<"\n\t Enter a year: ";
        cin>>y;
    }
    void check() {
        if((y%4==0 && y%100!=0) || y%400==0)
            cout<<"\n\t "<<y<<" is a leap year.";
        else
            cout<<"\n\t "<<y<<" is not a leap year.";
    }
};

int main() {
    leap_year l;
    l.getdata();
    l.check();
    return 0;
}