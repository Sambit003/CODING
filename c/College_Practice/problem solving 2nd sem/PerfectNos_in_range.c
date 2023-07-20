#include<stdio.h>
int main()
{
    int start,end,sum,i,j;
    printf("\n\tEnter the start and end points : ");
    scanf("%d%d",&start,&end);
    printf("\n\tPERFECT NUMBERS : ");
    for(i=start;i<=end;i++)
    {
        sum=0;
        for(j=1;j<i;j++)
        {
            if(i%j==0) sum+=j;
        }
        if(sum==j) printf("\t%d",sum);
    }
    return printf("\n\n\tPROGRAM EXECUTED SUCCESSFULLY");
}