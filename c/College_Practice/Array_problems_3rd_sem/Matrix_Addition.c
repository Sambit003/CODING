#include<stdio.h>
int main()
{
    int a[20][20],b[20][20],i,j,row,col; float check;
    printf("\n\tEnter the row and column of 1st matrix: ");
    scanf("%d%d",&row,&col);
    check=(row*0.2)+(col*0.3);
    printf("\n\tEnter the elements: ");
    for(i=0; i<row; i++)
    {
        printf("\n\trow no. %d: ",i+1);
        for(j=0; j<col; j++)
            scanf("%d",&a[i][j]);
    }
    printf("\n\tEnter the row and column of 2nd matrix: ");
    scanf("%d%d",&row,&col);
    if(check==(row*0.2)+(col*0.3))
    {
        printf("\n\tEnter the elements: ");
        for(i=0; i<row; i++)
        {
            printf("\n\trow no. %d: ",i+1);
            for(j=0; j<col; j++)
            {
                scanf("%d",&b[i][j]);
                a[i][j]=a[i][j]+b[i][j];
            }
        }
        printf("\n\tThe final matrix after addition: \n");
        for(i=0; i<row; i++)
        {
            for(j=0; j<col; j++)
                printf("\t%d",a[i][j]);
            printf("\n");
        }
    }
    else printf("\n\tAddition is not possible for different matrix order");
}