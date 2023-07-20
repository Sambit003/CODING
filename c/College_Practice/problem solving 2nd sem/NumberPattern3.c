#include<stdio.h>
int main()
{
    int i,j,k,row=0;
    printf("\n\tEnter the number of rows : ");
    scanf("%d",&row);
    for(i=1,k=1;i<=row;i++)
    {
        printf("\n\t");
        for(j=1;j<=i;j++,k++)
        {
            printf("%5d",k);
        }
    }
    return 0;
}