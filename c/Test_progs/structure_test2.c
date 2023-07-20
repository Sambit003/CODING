#include<stdio.h>
int main(void)
{
    struct data{
        int a,b;
    }x;
    printf("\n\tEnter the elements : ");
    scanf("%d%d",&x.a,&x.b);
    printf("\n\tSUM = %d",x.a+x.b);
    return(printf("\n\tProgram ran successfully"));
}