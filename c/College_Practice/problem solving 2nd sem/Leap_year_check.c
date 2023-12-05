#include<stdio.h>
int main()
{
    int year;
    printf("\n\tEnter year : ");
    scanf("%d",&year);
    //Ternary operator
    (year%4==0 && year%100!=0 || year%400==0)?printf("\n\tLeap year"):printf("\n\tNot a leap year");
}