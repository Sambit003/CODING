#include<stdio.h>
int main()
{
    int num,i,j;
    printf("\n\tEnter the number: ");
    scanf("%d",&num);
    printf("\n\n\tPrime Factors: ");
    for(i=1;i<=num;i++)
    {
        if(num%i==0)
        {
            if (i==2) printf("\t%d",i);
            if(i>2 && i%2!=0)
            {
                if (i==3 || i==5 || i==7)
                    printf("\t%d",i); 
                if ( i%3!=0 && i%5!=0 && i%7!=0)
                    printf("\t%d",i);
            }
        }
    }
    return printf("\n\n\tPROGRAM EXECUTED SUCCESSFULLY");
}