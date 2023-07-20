#include<stdio.h>
int main()
{
    int num=0,rev=0,q=0,r=0;
    printf("\n\tEnter the number : ");
    scanf("%d",&num);
    while(num!=0)
    {
        q=num/10;
        r=num%10;
        num=q;
        rev=(rev*10)+r;
    }
    printf("\n\tReverse of the number = %d",rev);
    return 0;
}