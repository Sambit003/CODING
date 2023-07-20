#include<stdio.h>
int main()
{
    float cel=0,farh=0;
    printf("\n\tEnter temperature (in Fahrenheit) : ");
    scanf("%f",&farh);
    cel=((farh-32)*5)/9;
    printf("\n\tEquivalent temperature in Celcius is : %f",cel);
    return 0;
}