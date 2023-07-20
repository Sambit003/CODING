// 2. Write a C program to check whether a number is Armstrong number or not using call by value.

#include <stdio.h>
#include <math.h>

int armstrongCheck(int num){
    int temp, sum = 0, rem, digits = 0;
    temp = num;
    while(temp != 0){
        digits++;
        temp /= 10;
    }
    temp = num;
    while(temp != 0){
        rem = temp % 10;
        sum += pow(rem, digits);
        temp /= 10;
    }
    if(sum == num)  return 1;
    else            return 0;
}


int main(){
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if(armstrongCheck(num) == 1)    printf("%d is an Armstrong number.", num);
    else                            printf("%d is not an Armstrong number.", num);
    return 0;
}