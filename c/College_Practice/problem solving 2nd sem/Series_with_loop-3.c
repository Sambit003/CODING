#include<stdio.h>
int main()
{
    int n,i,j,fact;
    float sum=1;
    printf("\n\tEnter the value of nth term : ");
    scanf("%d",&n);
    for(i=2;i<=n;i++)
    {
        fact=1;
        for(j=i+1;j>0;j--)
        {
            fact=fact*j;
        }
        sum=sum+((float)i/fact);
    }
    printf("\n\tSUM = %f",sum);
    return 0;
}