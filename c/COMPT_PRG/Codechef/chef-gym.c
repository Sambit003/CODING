#include<stdio.h>
int main()
{
    int t,x,y,z;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&x,&y,&z);
        if((x+y)<=z && y<z)
            printf("\n2");
        else if((x+y)>z && x<=z)
            printf("\n1");
        else
            printf("\n0");
    }
    return 0;
}