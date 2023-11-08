//WAP in C to implement radix sort.

/*
    What is Radix sort?
        Radix sort is a sorting algorithm that sorts the elements by first grouping the individual digits of the same place value. 
        Then, sort the elements according to their increasing/decreasing order.
        Radix sort is a linear time sorting algorithm that works on the principle of distributing the elements into buckets based on their radix value and then sort these buckets individually. 
        The radix value of an element is the value obtained by removing all the digits except the ones place, tens place, hundreds place, etc. 
        For example, the radix value of 123 is 3, and the radix value of 456 is 6.
        Radix sort is also known as bucket sort.
        Radix sort is a non-comparative sorting algorithm. 
        It avoids comparison by creating and distributing elements into buckets according to their radix value. 
        For elements with more than one significant digit, this bucketing process is repeated for every digit, while preserving the ordering of the prior step, until all digits have been considered. 
        For this reason, radix sort has also been called bucket sort and digital sort.
        Radix sort is a stable sort as relative order of elements with equal values is maintained.

    Algorithm:
        Step 1: Find the maximum element in the array.
        Step 2: Call the count sort function for each digit from 1 to the number of digits in the maximum element.
            Step 2a: Find the digit at the given place.
            Step 2b: Call the count sort function for the given digit.
                Step 2b.1: Create a count array of size 10.
                Step 2b.2: Store the count of each element in the count array.
                Step 2b.3: Modify the count array by adding the previous counts.
                Step 2b.4: Create an output array of size n.
                Step 2b.5: Find the index of each element of the original array in the count array.
                Step 2b.6: Place the elements in the output array.
                Step 2b.7: Copy the elements from the output array to the original array.
        Step 3: The array is sorted.
    
    Psedocode:
        radixSort(array)
            d <- maximum number of digits in the largest element
            create d buckets of size 0-9
            for i <- 0 to d
                sort the elements according to ith place digits using countSort
        countSort(array, d)

    Time Complexity:
        Best Case: O(nk)
        Average Case: O(nk)
        Worst Case: O(nk)
        where, n is the number of elements and k is the number of digits in the largest element.
*/

#include<stdio.h>
#include<stdlib.h>

// Function for finding the maximum element in the array
int find_max(int *arr, int n) {
    int max = arr[0];
    for(int i=1; i<n; i++)
    {
        if(arr[i] > max)
            max = arr[i];
    }
    return max;
}

// Function for counting sort. This function takes the array, size of the array and the exponent as the arguments.
/*
    This exponent is used to find the digit at the given place. 
    For example, if the exponent is 1, then the digit at the ones place is found.

    The count sort function is used to sort the array based on the digit at the given place. In Radix sort, this function is called multiple times.
*/
void count_sort(int *arr, int n, int exp) {
    int* output = (int*)calloc(n, sizeof(int));
    int count[10] = {0};
    for(int i=0; i<n; i++)   count[(arr[i]/exp)%10]++;
    
    for(int i=1; i<10; i++)  count[i] += count[i-1];

    for(int i=n-1; i>=0; i--) {
        int index = count[(arr[i]/exp)%10] - 1;
        output[index]=arr[i];
        count[(arr[i]/exp)%10]--;
    }

    for(int i=0; i<n; i++)   arr[i] = output[i];
    free(output);
    output = NULL;
}

// Function for radix sort
void radix_sort(int *arr, int n) {
    int max = find_max(arr, n);
    for(int exp=1; max/exp > 0; exp*=10)
        count_sort(arr, n, exp);
}

// Function for printing the array
void print_array(int *arr, int n) {
    for(int i=0; i<n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Main Function
int main() {
    int n=0, *arr = NULL;
    printf("\n\tEnter the number of elements: ");
    scanf("%d", &n);
    arr = (int*)calloc(n, sizeof(int));

    printf("\n\tEnter the elements: ");
    for(int i=0; i<n; i++)  scanf("%d", &arr[i]);

    printf("\n\tThe array before sorting: ");
    print_array(arr, n);

    radix_sort(arr, n);

    printf("\n\tThe array after sorting: ");
    print_array(arr, n);

    free(arr);
    arr = NULL;
    return 0;
}