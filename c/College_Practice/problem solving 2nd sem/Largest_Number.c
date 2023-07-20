#include<stdio.h>
int main()
{
    float a,b,c;
    printf("\n\tEnter three numbers : ");
    scanf("%f%f%f",&a,&b,&c);
    if(a>=b && a>c)
        printf("\n\tLargest number is : %f",a);
    else if(b>c)
        printf("\n\tLargest number is : %f",b);
    else
        printf("\n\tLargest number is : %f",c);
    return 0;
}