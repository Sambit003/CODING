#include<stdio.h>
int main()
{
    int n,i;
    float x[20],max=0,min=0;
    printf("\n\tEnter your range : ");
    scanf("%d",&n);
    if(n<=20 && n>0)
    {
        printf("\n\tEnter the elements : ");
        for(i=0;i<n;i++)
        {
            scanf("%f",&x[i]);
        }
        max=x[0];
        min=x[0];
        for(i=1;i<n;i++)
        {
            if(x[i]>max)
            {
                max=x[i];
            } 
            if(x[i]<min)
            {
                min=x[i];
            }
        }
        printf("\n\tMax number is : %f\n\tMin number is : %f",max,min);
    }
    else
        printf("\n\tOut of range !!");
    return 0;
}