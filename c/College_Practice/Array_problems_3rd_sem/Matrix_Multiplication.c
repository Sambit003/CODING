#include<stdio.h>
int main()
{
    int a[20][20],b[20][20],i,j,k,row,col,check;
    printf("\n\tEnter the number of row and column of 1st matrix: ");
    scanf("%d%d",&row,&col);
    check=col;
    printf("\n\tEnter the elements:");
    for(i=0;i<row;i++)
    {
        printf("\n\trow no. %d: ",i+1);
        for(j=0;j<col;j++)
            scanf("%d",&a[i][j]);
    }
    printf("\n\tEnter the number of row and column of 2nd matrix: ");
    scanf("%d%d",&row,&col);
    if(check==row)
    {
        int c[check][row];
        printf("\n\tEnter the elements:");
        for(i=0;i<row;i++)
        {
            printf("\n\trow no. %d: ",i+1);
            for(j=0;j<col;j++)
                scanf("%d",&b[i][j]);
        }
        for(i=0;i<check;i++)
        {
            for(j=0;j<row;j++)
                c[i][j]=a[i][j]*b[j][i];
        }
        printf("\n\tMatrix after multiplication:\n");
        for(i=0;i<check;i++)
        {
            for(j=0;j<row;j++)
                printf("\t%d",c[i][j]);
            printf("\n");
        }
    }
    else printf("\n\tMatrix multiplication is not possible if column of 1st matrix not equal to row of 2nd matrix");
    return 0;
}