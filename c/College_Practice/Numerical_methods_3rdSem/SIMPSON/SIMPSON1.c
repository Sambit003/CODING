#include<stdio.h>
#include<math.h>
float fx(float x){
    return (1/(1+x));
}
int main(){
    float x0, xn, h, sum=0;   int n;
    printf("\n\tEnter lower and upper limit of x, number of intervals: ");
    scanf("%f%f%d",&x0,&xn,&n);
    h=(xn-x0)/n;
    do{
        sum=sum+(h/3)*(fx(x0)+4*fx(x0+h)+fx(x0+2*h));
        printf("\n\tx0=%f\tx0+h=%f\tx0+2*h=%f\tf(x0)=%f\tf(x0+h)=%f\tf(x0+2*h)=%f",x0,x0+h,x0+2*h,fx(x0),fx(x0+h),fx(x0+2*h));
        x0=x0+2*h;
    }while(x0<xn);
    printf("\n\tThe Integral value is = %f",sum);
    return 0;
}