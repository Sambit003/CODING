#include<stdio.h>
int main()
{
    int num=0,temp=0,rev=0,r=0;
    printf("\n\tEnter the number : ");
    scanf("%d",&num);
    temp=num;
    while(temp!=0)
    {
        r=temp%10;
        temp=temp/10;
        rev=(rev*10)+r;
    }
    if(rev==num)
        printf("\n\tPalindrome");
    else
        printf("\n\tNot Palindrome");
    return 0;
}