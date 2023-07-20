#include <stdio.h> 
#include <math.h> 
float fx(float x) 
{
    return(pow(x,3)-5*x-7);
}
int main()
{
    float x1,x2,e,x0;
    printf("\n\tEnter the desired accuracy: "); 
    scanf("%f",&e);
    do 
    {
        printf("\n\tEnter interval x0,x1 : "); 
        scanf("%f %f",&x0,&x1);
    }while(fx(x0)*fx(x1)>0); 
    do 
    {
        x2=x0-(x0-x1)*(fx(x0)/(fx(x0)-fx(x1)));
        printf("\n\tx0=%f\tx1=%f\tx2=%f\tf(x2)=%f\tf(x0)=%f\tf(x1)=%f",x0,x1,x2,fx(x2),fx(x0),fx(x1));
        if (fx(x0)*fx(x2)<0)    x1=x2;   
        else    x0=x2;
    }while(fabs(fx(x2))>e);
    printf("\n\tRoot of the equation is %6.4f",x2);
    return 0;
}