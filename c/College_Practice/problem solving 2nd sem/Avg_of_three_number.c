#include<stdio.h>
int main()
{
    float avg=0,a,b,c;
    printf("\n\tEnter three numbers : ");
    scanf("%f%f%f",&a,&b,&c);
    avg=(a+b+c)/3;
    printf("\n\tAverage of those numbers, is : %f",avg);
    return 0;
}