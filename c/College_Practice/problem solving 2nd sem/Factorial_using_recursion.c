#include<stdio.h>
int fact(int num)
{
    if(num==1 || num==0)
        return 1;
    else
        return num*fact(num-1);
}
int main()
{
    int num;
    printf("\n\tEnter the number to get its factorial : ");
    scanf("%d",&num);
    printf("\n\tFactorial = %d",fact(num));
    return 0;
}
