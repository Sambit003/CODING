// This program is used to understand the concept of local variable.

#include<stdio.h>
int fun1()
{
    int i=0;
    i++;
    printf("\n\t%d",i);
    if (i=1){
        int i=2;
        printf("\n\t%d",i);
    }
    printf("\n\t%d",i);
    return 0;
}