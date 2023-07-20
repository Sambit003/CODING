#include<stdio.h>
int main()
{
    float cel=0,farh=0;
    printf("\n\tEnter temperature (in Celcius) : ");
    scanf("%f",&cel);
    farh=((cel/5)*9)+32;
    printf("\n\tEquivalent temperature in Celcius is : %f",farh);
    return 0;
}