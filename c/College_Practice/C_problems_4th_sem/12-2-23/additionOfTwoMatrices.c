#include<stdio.h>
#define SIZE 3

int main(){
    int arr1[SIZE][SIZE], arr2[SIZE][SIZE];

    //Take input from user
    for(int i = 0; i < 2; i++){
        printf("\n\tEnter the elements of array %d: ", i+1);
        for(int j = 0; j < SIZE; j++){
            printf("\n\tEnter the elements of row %d: ", j+1);
            for(int k = 0; k < SIZE; k++){
                if(i == 0)
                    scanf("%d", &arr1[j][k]);
                else
                    scanf("%d", &arr2[j][k]);
            }
        }
    }

    //Addition of two matrices
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            arr1[i][j] += arr2[i][j];
        }
    }

    //Print the resultant matrix
    printf("\n\tResultant matrix is: ");
    for(int i = 0; i < SIZE; i++){
        printf("\n");
        for(int j = 0; j < SIZE; j++){
            printf("\t%d ", arr1[i][j]);
        }
    }

    return 0;
}