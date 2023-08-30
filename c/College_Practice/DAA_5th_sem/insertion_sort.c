// WAP in C to simulate the working of Insertion Sort Algorithm.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sigint_handler(int sig) {
    printf("\n\n\tMEMORY ALLOCATION / DEALLOCATION / MANAGEMENT FAILED");
    printf("\n\n\tProgram terminated by user\n");
    exit(0);
}

void insertion_sort(int arr[], int n){
    int temp;
    for(int i = 1; i<=n; i++){
        temp=arr[i];
        int j=i-1;
        while(j>=0 && arr[j]>temp){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1] = temp;
    } 
}

bool is_sorted(int arr[], int n){
    for(int i=0; i<n-1; i++){
        if(arr[i] > arr[i+1]){
            return false;
        }
    }
    return true;
}

int main() {
    int n=-99, *arr=NULL; char ch;
    signal(SIGINT, sigint_handler);
    
    SET_SIZE: printf("\n\tEnter the array size: ");
    fflush(stdout);
    fflush(stdin);
    scanf("%d", &n);
    if (n>0){
        arr = (int *)calloc(n, sizeof(int));
        if (arr == NULL) {
            printf("\n\tMemory allocation failed.\n");
        }
        else { 
            printf("\n\tMemory allocation successful.\n");   
            while(1){
                printf("\n\tEnter the elements: ");
                for (int i = 0; i < n; i++) {
                    scanf("%d", &arr[i]);
                }

                if(is_sorted(arr, n)) printf("\n\tThe array is already sorted.\n");
                else {
                    printf("\n\tThe array is not sorted.\n\tSorting the array...\n");
                    insertion_sort(arr, n);
                    printf("\n\tThe sorted array is: ");
                    for (int i = 0; i < n; i++) {
                        printf("%d ", arr[i]);
                    }
                    printf("\n");
                }
                printf("\n\tDo you want to change the array size? (y/n): ");
                scanf(" %c", &ch);
                if(ch == 'y' || ch == 'Y') {
                    printf("\n\tDeallocating the memory");
                    if(arr != NULL){
                        printf("\n\tErasing the array: ");
                        for(int i=0; i<n; i++){
                            printf("\n\t[%d] ",i);
                            for(int j=0; j<4; j++){
                                printf("-");
                                sleep(1);
                            }
                            printf("> Garbage Dump Done");
                        }
                        free(arr);
                        arr = NULL;
                        n = -99;
                    }
                    if(arr == NULL) {
                        printf("\n\tMemory deallocated successfully.\n");
                        goto SET_SIZE;
                    }
                    else printf("\n\tMemory deallocation failed.\n");
                }
                else continue;
            }
        }
    }
    else {
        printf("\n\tInvalid array size.\n");
        goto SET_SIZE;
    }
    return 0;
}
