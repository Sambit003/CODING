// 1. Write a C program to print all Prime numbers between 1 to n using call by value.

#include <stdio.h>

int primeCheck(int num){
    int i, flag = 0;
    for(i = 2; i <= num/2; i++){
        if(num % i == 0){
            flag = 1;
            break;
        }
    }
    if(flag == 0)   return 1;
    else            return 0;
}

int main(){
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if(primeCheck(num) == 1)
        printf("%d is a prime number.", num);
    else
        printf("%d is not a prime number.", num);
    return 0;
}