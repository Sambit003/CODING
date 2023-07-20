#include<stdio.h>
int main()
{
    int n,i,sum=1,t=1;
    printf("\n\tEnter the value of nth term : ");
    scanf("%d",&n);
    for(i=2;i<=n;i++)
    {
        sum=sum+(2*i-1)*t;
        t=(-1)*t;
    }
    printf("\n\tSUM = %d",sum);
    return 0;
}