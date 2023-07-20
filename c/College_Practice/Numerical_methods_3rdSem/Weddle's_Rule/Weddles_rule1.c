#include<stdio.h>
#include<math.h>

float fx(float x){
    return 1.0/sqrt(1-pow(x,2));
}

int main(){
    float x0,xn,h,sum=0;    int n;
    printf("\n\tEnter the lower limit, upper limit and number of sub-intervals: ");
    scanf("%f%f%d",&x0,&xn,&n);
    h=(xn-x0)/n;
    do{
        sum+=(3*h/10)*(fx(x0)+5*fx(x0+h)+fx(x0+2*h)+6*fx(x0+3*h)+fx(x0+4*h)+5*fx(x0+5*h)+fx(x0+6*h));
        printf("\n\tSUM=%f",sum);
        x0+=6*h;
    }while(x0<xn);
    printf("\n\tThe value of the integral is: %5.3f",sum);
    return 0;
}