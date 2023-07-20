#include<stdio.h>
int main()
{
    int i,n,n1=0,n2=1,n3=0;
    printf("\n\tEnter the value of nth term : ");
    scanf("%d",&n);
    printf("\n\tSeries :\t%d\t%d",n1,n2);
    for(i=2;i<n;i++)
    {
        n3=n1+n2;
        printf("\t%d",n3);
        n1=n2;
        n2=n3;
    }
    return 0;
}