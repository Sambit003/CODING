/* Topic: Array Manipulation
Description: Given an array of integers, find two numbers such that they add up to a specific target sum. Return their indices.

Example:
Input: [2, 7, 11, 15], target=9
Output: index1=0, index2=1
*/

#include <stdio.h>
#include <stdlib.h>

int* twoSum(int nums[], int size, int target, int* returnSize){
    int *arr = (int *)malloc(2*sizeof(int));
    for(int i=0; i<size; i++){
        for(int j=i+1; j<size; j++){
            if((int)nums[i]+(int)nums[j] == target){
                arr[0] = i;
                arr[1] = j;
                *returnSize = 2;
                return arr;
            }
        }
    }
    return arr;
}

// Driver code
int main(){
    int n, target;
    printf("Enter the size of array: ");
    scanf("%d", &n);
    int *arr = (int *)malloc(n*sizeof(int));

    printf("Enter the elements of array: ");
    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }

    printf("Enter the target sum: ");
    scanf("%d", &target);

    int *returnSize = (int *)malloc(sizeof(int));
    int *result = twoSum(arr, n, target, returnSize);
    printf("index1=%d, index2=%d", result[0], result[1]);
    return 0;
}
