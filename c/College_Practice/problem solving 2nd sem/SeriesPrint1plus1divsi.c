#include<stdio.h>
int main()
{
    int i,term;
    float sum=0;
    printf("\n\tEnter the nth term : ");
    scanf("%d",&term);
    for(i=1;i<=term;i++)
        sum+=1.0/i;
    printf("\n\tSUM = %f",sum);
    return printf("\n\n\tPROGRAM EXECTED SUCCESSFULLY");  
}