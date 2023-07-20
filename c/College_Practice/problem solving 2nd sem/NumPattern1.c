#include<stdio.h>
int main()
{
    int nrow,i,j;
    printf("\n\tEnter the number of rows : ");
    scanf("%d",&nrow);
    for(i=1;i<=nrow;i++)
    {
        printf("\n\t");
        for(j=1;j<=i;j++)
        {
            printf("%d",j);
        }
    }
    return 0;
}