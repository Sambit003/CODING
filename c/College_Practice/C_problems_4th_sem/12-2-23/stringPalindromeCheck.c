// Write a C program to check whether a string is palindrome or not (using single string only).

#include <stdio.h>
#include <string.h>

int main()
{
    //Declare a string and initialize it with a word.
    char str[100];
    int length = 0, flag = 0;

    //Get the string from the user.
    printf("\n\tEnter a word: ");
    gets(str);

    //Calculate the length of the string.
    length = strlen(str);

    //Check if the string is a palindrome.
    for (int i = 0; i < length; i++){
        if (str[i] != str[length - i - 1]){
            flag++;
            break;
        }
    }

    //Print the result.
    if (flag == 1)  printf("\n\tThe word is not a palindrome.");
    else    printf("\n\tThe word is a palindrome.");

    return 0;
}