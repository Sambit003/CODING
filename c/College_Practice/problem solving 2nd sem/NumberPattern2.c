#include<stdio.h>
int main()
{
    int row,i,j1,j2;
    printf("\n\tEnter the number of rows : ");
    scanf("%d",&row);
    for(i=1;i<=row;i++)
    {
        printf("\n\t");
        for(j1=2;j1<=i;j1++)
        {
            printf(" ");
        }
        for(j2=row;j2>=i;j2--)
        {
            printf("%d",i);
        }
    }
    return 0;
}
