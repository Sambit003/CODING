#include<stdio.h>
int main()
{
    int t,x,y;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&x);
        scanf("%d",&y);
        if((100*x)<(10*y))
            printf("\nDisposable");
        else
            printf("\nCloth");
    }
    return 0;
}