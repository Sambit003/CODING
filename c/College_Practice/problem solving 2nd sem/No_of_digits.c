#include<stdio.h>
int main()
{
    int num=0,count=0,q=0,r=0;
    printf("\n\tEnter the number : ");
    scanf("%d",&num);
    while(num!=0)
    {
        q=num/10;
        r=num%10;
        num=q;
        count++;
    }
    printf("\n\tNumber of digit = %d",count);
    return 0;
}