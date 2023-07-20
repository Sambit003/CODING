#include<stdio.h>
void main()
{
    int mat[20][20],i,j,row=0,col=0,sumr,sumd=0;
    printf("\n\tEnter the number of rows & column : ");
    scanf("%d%d",&row,&col);
    if((row>0 && row<=20) && (col>0 && col<=20))
    {
        for(i=0;i<row;i++)
        {
            printf("\n\tEnter the element of %d row : ",i+1);
            for(j=0;j<col;j++)
                scanf("%d",&mat[i][j]);
        }
        printf("\n\n\t::Sum of row elements::");
        for(i=0;i<row;i++)
        {   
            sumr=0;
            for(j=0;j<col;j++)
                sumr=sumr+mat[i][j];
            printf("\n\t%d row : %d",i+1,sumr);
        }
        printf("\n\n\t::Sum of Diagonals::");
        if(row==col)
        {
            for(i=0,j=0;i<row,j<col;i++,j++)
                sumd=sumd+mat[i][j];
            printf("\n\tSum of left to right diagonal = %d",sumd);
            sumd=0;
            for(i=0,j=col-1;i<row,j>=0;i++,j--)
                sumd=sumd+mat[i][j];
            printf("\n\tSum of right to left diagonal = %d",sumd);
        }
        else
            printf("\n\t\t!! ERROR !! \n\t criteria for getting sum of diagonals : Matrix should be a square matrix");
    }
    else
        printf("\n\tMaximum limit of the 2D matrix is 20x20");
}