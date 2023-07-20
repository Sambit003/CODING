#include<stdio.h>
float swap(float a, float b)
{
    float c;
    c=a;
    a=b;
    b=c;
    return (printf("\n\tAfter swapping :\n\tElement in a : %f\n\tElement in b : %f",a,b));
}
int main()
{
    float a,b;
    printf("\n\tEnter element in a : ");
    scanf("%f",&a);
    printf("\n\tEnter element in b : ");
    scanf("%f",&b);
    swap(a,b);
    return 0;
}