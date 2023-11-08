// WAP in C to implement quick sort algorithm

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_sorted(int *arr, int n){
    for (int i = 0; i < n - 1; i++)
        if (arr[i] > arr[i + 1])
            return false;

    return true;
}

void swap(int *a, int *b){
    int temp = *a;
    *a=*b;
    *b=temp;
}

int partition(int *arr, int low, int high){
    int pivot = arr[high], i=low-1;
    for(int j=low; j<high; j++){
        if(arr[j]<=pivot){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i+1], &arr[high]);
    return i+1;
}

void quick_sort(int *arr, int low, int high){
    if(low < high){
        int part_index = partition(arr,low,high);
        quick_sort(arr, low, part_index-1);
        quick_sort(arr, part_index+1, high);
    }
}

int main(){
    int n, *arr=NULL;
    printf("\n\tEnter the size of the array: ");
    scanf("%d", &n);
    arr = (int *)calloc(n, sizeof(int));
    printf("\n\tEnter the elements of the array: ");
    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }
    if(is_sorted(arr, n)){
        printf("\n\tThe array is already sorted.\n");
    }
    else{
        printf("\n\tThe array is not sorted.\n\tSorting the array...\n");
        quick_sort(arr, 0, n-1);
        printf("\n\tThe array has been sorted.\n");
    }
    printf("\n\tThe sorted array is: ");
    for(int i=0; i<n; i++){
        printf("%d ", arr[i]);
    }
    free(arr);
    arr=NULL;
    return 0;
}