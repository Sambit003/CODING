#include<stdio.h>
int main()
{
    int pass,term,i,j;
    double sinsum=0,cossum=1,sum=0,termcal,x,pow,fact;
    printf("\n\t::tan(X) series::\n\tEnter the value of X and terms:");
    scanf("%lf%d",&x,&term);
    x*=(3.14159/180);
    for(pass=1;pass<=term;pass++)
    {
        pow=1.0; fact=1;
        for(i=1;i<=2*pass-1;i++)
        {
            pow*=x;
        }
        for(j=2*pass-1;j>0;j--)
        {
            fact*=j;
        }
        if(pass%2!=0) sinsum+=(pow/fact);
        else sinsum-=(pow/fact);
    }
    for(pass=1;pass<=term;pass++)
    {
        pow=1.0; fact=1;
        for(i=1;i<=2*pass;i++)
        {
            pow*=x;
        }
        for(j=2*pass;j>0;j--)
        {
            fact*=j;
        }
        if(pass%2!=0)   cossum-=(pow/fact);
        else    cossum+=(pow/fact);
    }
    printf("\n\tSUM = %lf",(sinsum/cossum));
    return printf("\n\n\tPROGRAM EXECUTED SUCCESSFULLY");
}