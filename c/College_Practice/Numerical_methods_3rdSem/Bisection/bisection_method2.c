#include<stdio.h>
#include<math.h>
float f(float x)
{
    float fx=(2*x)-(3*sin(x))-5;
    return fx;
}
int main()
{
    float x0,a,b,e;
    printf("\n\tEnter the desired accuracy: ");
    scanf("%f",&e);
    do{
        printf("\n\tEnter the interval: ");
        scanf("%f%f",&a,&b);
    }while(f(a)*f(b)>0);
    printf("\n\tThe interval is [%f,%f]\n",a,b);
    do{
        x0=(a+b)/2;
        printf("\n\t a=%f\t b=%f\t x0=%f\t f(x0)=%f",a,b,x0,f(x0));
        if(f(a)*f(x0)<0) b=x0;
        else a=x0;
    }while(fabs(b-a)>=e);
    printf("\n\n\tThe root of the equation is: %5.3f",x0);
    return 0;
}