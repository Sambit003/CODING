#include<stdio.h>
int power(int x,int n)
{
    int pow=1,i;
    for(i=0;i<n;i++)
        pow=pow*x;
    return pow;
}
void main()
{
    int x,n;
    printf("\n\tEnter the value of x : ");
    scanf("%d",&x);
    printf("\n\tEnter the value of power : ");
    scanf("%d",&n);
    printf("\n\t%d to the power %d = %d",x,n,power(x,n));
}