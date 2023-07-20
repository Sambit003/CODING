#include<stdio.h>
int main()
{
    float area=0,base=0,height=0;
    printf("\n\tEnter base and height : ");
    scanf("%f%f",&base,&height);
    area=0.5*base*height;
    printf("\n\tArea of the triangle is %f",area);
    return 0;
}