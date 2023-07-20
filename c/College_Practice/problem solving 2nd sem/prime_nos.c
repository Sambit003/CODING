#include<stdio.h>
int main()
{
    int i,j,n1,n2;
    printf("\n\tEnter the range (by providing a space): ");
    scanf("%d%d",&n1,&n2);
    printf("\n\tPrime numbers available : ");
    for(j=n1;j<n2;j++)
    {
        if (j==2)
            printf("\t%d",j);
        if(j>2 && j%2!=0)
        {
            if (j==3 || j==5 || j==7)
               printf("\t%d",j); 
            if ( j%3!=0 && j%5!=0 && j%7!=0)
                printf("\t%d",j);
        }
    }
    return 0;
}