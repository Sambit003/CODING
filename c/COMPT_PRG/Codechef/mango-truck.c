#include<stdio.h>
int main()
{
    int t,x,y,z;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&x,&y,&z);
        if((x+y)<=z)
            printf("\n%d",(z-y)/x);
        else
            printf("\n0");
    }
    return 0;
}