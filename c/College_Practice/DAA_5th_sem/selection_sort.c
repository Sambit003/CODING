// WAP to implement selection sort algorithm

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

bool is_sorted(int *arr, int n){
    for(int i=0; i<n-1; i++){
        if(arr[i] > arr[i+1]){
            return false;
        }
    }
    return true;
}

void selection_sort (int arr[], int n){
    for (int i = 0; i < n - 1; i++) {
        // Find the index of the minimum element in the unsorted part
        int minIndex = i;
        
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        
        // Swap the found minimum element with the first element of the unsorted part
        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
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
        selection_sort(arr, n);
        printf("\n\tThe array has been sorted.\n");
    }
    printf("\n\tThe sorted array is: ");
    for(int i=0; i<n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    arr=NULL;
    return 0;
}