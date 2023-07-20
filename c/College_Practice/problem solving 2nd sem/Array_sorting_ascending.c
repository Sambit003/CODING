#include<stdio.h>
int main()
{
    int n,i,j,temp=0,x[20];
    printf("\n\tEnter your range : ");
    scanf("%d",&n);
    if(n<=20 && n>0)
    {
        printf("\n\tEnter the elements : ");
        for(i=0;i<n;i++)
        {
            scanf("%d",&x[i]);
        }
        for(j=0;j<n-1;j++)
        {
            for(i=0;i<(n-1-j);i++)
            {
                if(x[i]>x[i+1])
                {
                    temp=x[i];
                    x[i]=x[i+1];
                    x[i+1]=temp;
                }
            }
        }
        printf("\n\tArray sorting done : ");
        for(i=0;i<n;i++)
        {
            printf("\t%d",x[i]);
        }
    }
    else
        printf("\n\tOut of range !!");
    return 0;
}