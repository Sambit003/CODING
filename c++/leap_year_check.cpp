// WAP in C++ to check whether the year is leap year or not

#include<iostream>
using namespace std;

int main(){
    int year;
    cout<<"\n\tEnter a year: ";
    cin>>year;
    if(year%400==0 || (year%4==0 && year%100!=0)){
        cout<<"\n\t"<<year<<" is a leap year";
    }
    else{
        cout<<"\n\t"<<year<<" is not a leap year";
    }
    return 0;
}