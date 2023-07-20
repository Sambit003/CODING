// Write a program in C to implement Insertion Short
#include <stdio.h>
#include <stdlib.h>

// Function to sort an array using insertion sort
void insertionSort(int array[], int n)
{
    int i, element, j;
    for (i = 1; i < n; i++) {
        element = array[i];
        j = i - 1;

        // Move elements of array[0..i-1], that are
        // greater than element, to one position ahead
        // of their current position
        while (j >= 0 && array[j] > element) {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = element;
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
    int n = sizeof(data) / sizeof(data[0]);

    insertionSort(data, n);
    printArray(data, n);

    return 0;
}