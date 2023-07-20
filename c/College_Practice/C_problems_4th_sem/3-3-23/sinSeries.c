// 3. Write a C program to find value of sin series using call by value.

#include <stdio.h>
#include <math.h>

float sinSeries(int x, int n){
    float sum = 0;
    for(int i = 1; i <= n; i++){
        sum += pow(-1, i-1) * pow(x, 2*i-1) / tgamma(2*i);
    }
    return sum;
}


int main(){
    int x, n;
    printf("Enter the value of x: ");
    scanf("%d", &x);
    printf("Enter the value of n: ");
    scanf("%d", &n);

    printf("sin(%d) = %f", x, sinSeries(x, n));
}