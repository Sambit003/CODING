// WAP in C to implement merge sort algorithm

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_sorted(int *arr, int n){
    for (int i = 0; i < n - 1; i++)
        if (arr[i] > arr[i + 1])
            return false;

    return true;
}


void merge(int arr[], int left, int right){
    int size = (right - left) + 1;
    int mid = (left + right) / 2;
    int *merge_arr = (int *)calloc(size, sizeof(int));
    if (merge_arr == NULL)  printf("\n\tMemory allocation failed\n");
    else{
        int i = left, j = mid + 1, k = left;
        while(i<=mid && j<=right){
            if(arr[i] <= arr[j])    merge_arr[k++] = arr[i++];
            else    merge_arr[k++] = arr[j++];
        }
        while(i<=mid)   merge_arr[k++] = arr[i++];
        while(j<=right) merge_arr[k++] = arr[j++];

        for (int k = left; k <= right; k++) arr[k] = merge_arr[k];
    }
}

void merge_sort(int arr[], int left, int right){
    if (left<right){
        int middle = (left+right)/2;
        merge_sort(arr, left, middle);
        merge_sort(arr, middle+1, right);

        merge(arr, left, right);
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
        merge_sort(arr, 0, n-1);
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