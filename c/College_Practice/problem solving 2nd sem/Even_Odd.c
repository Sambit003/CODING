#include<stdio.h>
int main()
{
    int num=0;
    printf("\n\tEnter the number : ");
    scanf("%d",&num);
    if(num%2==0)
        printf("\n\tEVEN NUMBER");
    else
        printf("\n\tODD NUMBER");
    return 0;
}