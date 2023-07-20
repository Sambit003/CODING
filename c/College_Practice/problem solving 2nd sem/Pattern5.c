#include<stdio.h>
int main()
{
    int nrow,i,j1,j2;
    printf("\n\tEnter the number of rows : ");
    scanf("%d",&nrow);
    for(i=1;i<=nrow;i++)
    {
        printf("\n\t");
        for(j1=nrow;j1>i;j1--)
        {
            printf(" ");
        }
        for(j2=1;j2<=i;j2++)
        {
            printf("* ");
        }
    }
    return 0;
}