//Write a C program to reverse an array using user defined function and pointer.
#include<stdio.h>
#include<stdlib.h>
#define SIZE 10

void reverse(int *arr){
    int temp;
    for(int i=0;i<SIZE/2;i++){
        temp = arr[i];
        arr[i] = arr[SIZE-i-1];
        arr[SIZE-i-1] = temp;
    }
}

int main(){
    int arr[SIZE];
    printf("\n\tEnter elements in the array: ");
    for(int i=0;i<SIZE;i++){
        scanf("%d", &arr[i]);
    }
    reverse(arr);
    printf("\n\tThe array after reversing is: ");
    for(int i=0;i<SIZE;i++){
        printf("%d ", arr[i]);
    }
    return 0;
}