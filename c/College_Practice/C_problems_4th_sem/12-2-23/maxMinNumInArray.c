#include<stdio.h>
#define SIZE 5

int main(){
    //Declare Integer varibales max, min ; and Integer array arr
    int max, min, arr[SIZE];

    //Take input from user
    printf("\n\tEnter the elements: ");
    for(int i=0; i<SIZE; i++)
        scanf("%d", &arr[i]);

    //Initialize max and min with first element of array
    max = min = arr[0];

    //Iterate through array and find max and min
    for(int i=1; i<SIZE; i++){
        //If current element is greater than max, then update max
        if(arr[i] > max)
            max = arr[i];
        //If current element is less than min, then update min
        if(arr[i] < min)
            min = arr[i];
    }

    //Print max and min
    printf("\n\tMaximum: %d   &   Minimum: %d", max, min);
    return 0;
}