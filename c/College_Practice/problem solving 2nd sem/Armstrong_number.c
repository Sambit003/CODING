#include<stdio.h>
int main()
{
    int num=0,temp,count=0,r=0,i,sum=0,pow;
    printf("\n\tEnter the number : ");
    scanf("%d",&num);
    temp=num;
    while(temp!=0)
    {
        temp=temp/10;
        count++;
    }
    temp=num;
    while(temp!=0)
    {
        r=temp%10;
        temp=temp/10;
        pow=1;
        for(i=1;i<=count;i++)
        {
            pow=pow*r;
        }
        sum=sum+pow;
    }
    if(num==sum)
        printf("\n\tARMSTRONG");
    else
        printf("\n\tNOT ARMSTRONG");
    return 0;
}