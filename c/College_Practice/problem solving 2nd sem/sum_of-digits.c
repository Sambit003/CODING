#include<stdio.h>
int main()
{
    int num=0,sum=0,q=0,r=0;
    printf("\n\tEnter the number : ");
    scanf("%d",&num);
    while(num!=0)
    {
        q=num/10;
        r=num%10;
        num=q;
        sum=sum+r;
    }
    printf("\n\tSum of digit = %d",sum);
    return 0;
}