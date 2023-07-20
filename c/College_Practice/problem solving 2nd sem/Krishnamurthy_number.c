#include<stdio.h>
int main()
{
    int num=0,temp,count=0,r=0,i,sum=0,fact;
    printf("\n\tEnter the number : ");
    scanf("%d",&num);
    temp=num;
    while(temp!=0)
    {
        r=temp%10;
        temp=temp/10;
        fact=1;
        for(i=r;i>0;i--)
        {
            fact=fact*i;
        }
        sum=sum+fact;
    }
    if(num==sum)
        printf("\n\tKRISHNAMURTHY NUMBER");
    else
        printf("\n\tNOT KRISHNAMURTHY NUMBER");
    return 0;
}