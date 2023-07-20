/* 
    NOTE: Provide user two options: 1. For calculating the frrquency of each element in array 
                                    2. For calculating the frequency of a particular element in array
*/

#include<stdio.h>
#include<stdlib.h>
#define SIZE 5

int main(){
    // Declare Integer array arr, checkedElement[] and Integer variables frequency and searchElement and Character variable choice
    int arr[SIZE], checkedElement[SIZE], frequency = 0, searchElement;
    char choice;

    //Take input from user
    printf("\n\tEnter the elements: ");
    for(int i=0; i<SIZE; i++)
        scanf("%d", &arr[i]);
    
    //Get into the menu driven program
    while(1){
        printf("\n\t1. Get the frequency of each element automatically\n\t2. Get the frequency of a particular element\n\t3. Exit\n\t-------------------------------------------------------------");
        printf("\n\tEnter your choice: ");
        fflush(stdin);
        scanf("%c", &choice);

        switch(choice){
            case '1':
                //This module will check the frequency of each element in array, and if the element is already checked, then it will not check it again
                //it can be done by using a new array checkedElement[], which will store the elements which are already checked

                //Initialize checkedElement[] with 0
                for(int i=0; i<SIZE; i++)
                    checkedElement[i] = 0;
                
                //Iterate through array and check the frequency of each element
                for(int i=0; i<SIZE; i++){
                    //If the element is already checked, then skip it
                    if(checkedElement[i] == 1)
                        continue;
                    //If the element is not checked, then check it
                    else{
                        //Initialize frequency with 0
                        frequency = 0;
                        //Iterate through array and check the frequency of current element
                        for(int j=0; j<SIZE; j++){
                            if(arr[i] == arr[j]){
                                frequency++;
                                checkedElement[j] = 1;
                            }
                        }
                        //Print the frequency of current element
                        printf("\n\tFrequency of %d is %d", arr[i], frequency);
                    }
                }
                printf("\n\n");
                break;
            case '2':
                //This module will check the frequency of a particular element in array
                printf("\n\tEnter the element to search: ");
                scanf("%d", &searchElement);
                frequency = 0;
                for(int i=0; i<SIZE; i++){
                    if(arr[i] == searchElement)
                        frequency++;
                }
                printf("\n\tFrequency of %d is %d", searchElement, frequency);
                break;
            case '3':
                //Exit from the program
                exit(1);
                break;
            default:
                //If user enters wrong choice, then print error message
                printf("\n\tWrong choice\n\n");
                break;
        }
    }

    return 0;
}