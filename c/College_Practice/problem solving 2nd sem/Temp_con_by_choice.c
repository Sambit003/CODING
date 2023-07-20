#include<stdio.h>
int main()
{
    int choice;
    float cel=0,farh=0;
    printf("\n\tMode of conversion\n\n\t1. Celcius to fahrenheit\n\t2. Fahrenheit to Celcius\n\n\tEnter choice (number only) : ");
    scanf("%d",&choice);
    if(choice==1)
    {
        printf("\n\tEnter temperature (in Celcius) : ");
        scanf("%f",&cel);
        farh=((cel/5)*9)+32;
        printf("\n\tEquivalent temperature in Fahrenheit is : %f",farh);
    }
    else if(choice==2)
    {
        printf("\n\tEnter temperature (in Fahrenheit) : ");
        scanf("%f",&farh);
        cel=((farh-32)*5)/9;
        printf("\n\tEquivalent temperature in Celcius is : %f",cel);
    }
    else
        printf("\n\tEnter choice correctly");
    return 0;
}