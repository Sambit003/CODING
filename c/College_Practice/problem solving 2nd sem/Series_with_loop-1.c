#include<stdio.h>
int main()
{
    int n,i,sum=0;
    printf("\n\tEnter the value of nth term : ");
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        sum=sum+(2*i-1);
    }
    printf("\n\tSUM = %d",sum);
    return 0;
}