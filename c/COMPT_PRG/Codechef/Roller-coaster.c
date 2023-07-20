#include<stdio.h>
int main()
{
    int t,x,h;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&x);
        scanf("%d",&h);
        if(x>h || x==h)
            printf("\n\tYes");
        else
            printf("\n\tNo");
    }
    return 0;
}