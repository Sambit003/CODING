//Write a C Program to swap two given numbers using user defined function and pointer.

#include<stdio.h>
#include<stdlib.h>

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(){
    int a, b;
    printf("\n\tEnter the value of a & b: ");
    scanf("%d %d", &a, &b);
    printf("\n\tThe value of a & b before swapping is: %d %d",a,b);
    swap(&a, &b);
    printf("\n\tThe value of a & b after swapping is: %d %d",a,b);
    return 0;
}