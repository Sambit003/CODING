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
    int num, i;
    printf("Enter the upperbound: ");
    scanf("%d", &num);
    printf("Prime numbers between 1 to %d are: ", num);
    for(i = 2; i <= num; i++){
        if(primeCheck(i) == 1)
            printf("%d ", i);
    }
    return 0;
}