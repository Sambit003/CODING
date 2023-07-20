// 6. Write a C program to find the Fibonacci series up to n term using recursive function.

#include <stdio.h>

int fibonacci(int n){
    if(n == 1 || n == 2)    return 1;
    else                    return fibonacci(n-1) + fibonacci(n-2);
}

int main(){
    int n;
    printf("Enter the number of terms: ");
    scanf("%d", &n);
    printf("The Fibonacci series is: ");
    for(int i = 1; i <= n; i++){
        printf("%d ", fibonacci(i));
    }
    return 0;
}