#include<stdio.h>
int main()
{
    int n,i;
    float x[20],sum=0,avg=0;
    printf("\n\tEnter your range : ");
    scanf("%d",&n);
    if(n<=20 && n>0)
    {
        printf("\n\tEnter the elements : ");
        for(i=0;i<n;i++)
        {
            scanf("%f",&x[i]);
            sum=sum+x[i];
        }
        avg=sum/n;
        printf("\n\tAverage of the elements : %f",avg);
    }
    else
        printf("\n\tOut of range !!");
    return 0;
}