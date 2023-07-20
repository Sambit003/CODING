// Write a C program to copy one array to another using user defined function and pointer.

#include <stdio.h>
#define SIZE 10

void copy(int *arr1, int *arr2){
    for(int i=0;i<SIZE;i++){
        arr2[i] = arr1[i];
    }
}

int main(){
    int arr1[SIZE], arr2[SIZE];
    printf("\n\tEnter elements in the array: ");
    for(int i=0;i<SIZE;i++){
        scanf("%d", &arr1[i]);
    }
    copy(arr1, arr2);
    printf("\n\tThe array after copying is: ");
    for(int i=0;i<SIZE;i++){
        printf("%d ", arr2[i]);
    }
    return 0;
}