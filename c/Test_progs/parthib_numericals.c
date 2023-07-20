#include<stdio.h>
#include<stdlib.h>
#include<math.h>

float f(float x0);

int main()
{
    int N;
    float x0,xn,h,sum=0;
    printf("\nInitial and Final Base values and Intervals:");
    scanf("%f%f%d",&x0,&xn,&N);
    h=(xn-x0)/N;
    do
    {
        sum=sum+(3*h/10)*(f(x0)+5*f(x0+h)+f(x0+2*h)+6*f(x0+3*h)+f(x0+4*h)+5*f(x0+5*h)+f(x0+6*h));
        printf("\n\n\tsum:%f",sum);
        x0+=(6*h);
    } while (x0<xn);
    printf("\n\n\tAREA UNDER THE CURVE:%f\n",sum);
    return 0;
}

float f(float x0)
{
    while(1)
    {
        int choice;
        printf("\n\n\tEnter 1-3");
        scanf("%d",&choice);
        switch (choice)
        {
            case 1:
                return (1.0/(1.0+x0));
                break;
        
            case 2:
                return ((pow(x0,2)+2)/(pow(x0,2)+1));
                break;

            case 3:
                return (1.0/sqrt(1-pow(x0,2)));
                break;
            
            default:
                exit(1);
        }
    }
}