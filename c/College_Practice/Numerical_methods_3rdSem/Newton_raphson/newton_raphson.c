#include<stdio.h>
#include<math.h>
float fx(float x){
    return (pow(x,3)-x-4);
}
float f_dash(float x){
    return (3*pow(x,2)-1);
}
void main(){
    float x_lower,x_upper,x0,x1,e,accuracy;
    do{
        printf("\n\tEnter the interval: ");
        scanf("%f%f",&x_lower,&x_upper);
    }while(fx(x_lower)*fx(x_upper)>0);
    printf("\n\tThe interval is [%f,%f]\n",x_lower,x_upper);
    printf("\n\tEnter the desired accuracy: ");
    scanf("%f",&e);
    x0=x_lower;
    do{
        x0=x1;
        x1=x0-(fx(x0)/f_dash(x0));
        printf("\n\tx0=%f\tf(x0)=%f\tf'(x0)=%f\t|x1-x0|=%f",x0,fx(x0),f_dash(x0),fabs(x1-x0));
        accuracy=fabs(x1-x0);
    }while(accuracy>e);
    printf("\n\n\tThe root of the equation is: %6.4f",x0);  
}