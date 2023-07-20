/* Bisection Method */ 
#include<stdio.h> 
#include<conio.h> 
#include<math.h> 
/*function*/
float f(float x) 
{
float f1;
f1= pow(x,3) – x -4; 
return(f1);
}
/* Main Program */ 
main()
{
float a,b,e,x0,N; 
int k;
clrscr();
printf(“\n Enter accuracy”); 
scanf(“%f”, &e);
do 
{
printf(“\n Enter interval a,b”); 
scanf(“%f%f”,&a,&b);
}while(f(a)*f(b) > 0); 
k=0;
do 
{
a|=%f”,k+1,a,b,x0,f(x0),fabs(b-a)); 
if (f(a)*f(x0) < 0)
{
b = x0;
}
7
|b-
x0=(a+b)/2;
printf(“\nI=%d a=%f b=%f x0=%f f(x0)=%f 8
else
{
a = x0; 
}
k=k+1;
}while(fabs(b-a) > e);
printf(“\n Root of the equation is % 6.4f”,x0);
printf(“\n Actual no.of iterations required to achieve desired accuracy,%d”,k); 
getch();
}