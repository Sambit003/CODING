#include<stdio.h>
int main()
{
    int year;
    printf("\n\tEnter year : ");
    scanf("%d",&year);
    if((year%4==0 && year%100!=0) || year%400==0)
        printf("\n\tLEAP YEAR");
    else
        printf("\n\tNOT LEAP YEAR");
    return 0;
}