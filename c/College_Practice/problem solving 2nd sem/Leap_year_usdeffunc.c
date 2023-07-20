#include<stdio.h>
char* leapyear(int year)
{
    if((year%4==0 && year%100!=0) || year%400==0)
        return "LEAP YEAR";
    else
        return "NOT LEAP YEAR";
}
int main()
{
    int year;
    printf("\n\tEnter year : ");
    scanf("%d",&year);
    printf("\n\t%s",leapyear(year));
    return 0;
}