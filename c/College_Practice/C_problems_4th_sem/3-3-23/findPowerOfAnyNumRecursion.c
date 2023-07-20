// 7. Write a C program to find power of any number using recursive function.

#include <stdio.h>

int power(int num, int pow){
    if(pow == 0)    return 1;
    else            return num * power(num, pow-1);
}

int main(){
    int num, pow;
    printf("Enter the number: ");
    scanf("%d", &num);
    printf("Enter the power: ");
    scanf("%d", &pow);
    printf("%d to the power %d is %d", num, pow, power(num, pow));
    return 0;
}