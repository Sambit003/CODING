//Write a program in C to implement Selection Sort

#include <stdio.h>
#include <stdlib.h>

// Function of selection sort
void selectionSort(int arr[], int n){
    int i, j, min, temp;
    for (i = 0; i < n-1; i++){
        min = i;
        for (j = i + 1; j < n; j++){
            if (arr[j] < arr[min]){
                min = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

// Function to print an array
void printArray(int array[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", array[i]);
}

// Driver code
int main()
{
    int data[] = { 9, 5, 1, 4, 3 };
    int n = sizeof(data) / sizeof(data[0]); //this is the size of the array calculated by dividing the size of the array by the size of the data type of the array

    selectionSort(data, n);
    printArray(data, n);

    return 0;
}