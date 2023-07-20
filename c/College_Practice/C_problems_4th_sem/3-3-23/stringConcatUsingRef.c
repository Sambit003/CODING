// 5. Write a C program to concatenate two strings using call by reference.

#include <stdio.h>
#include <string.h>

// Function to concatenate two strings
char stringConcat(char* str1, char* str2){
    int i, j;
    for(i = strlen(str1), j = 0; j < strlen(str2); i++, j++){
        str1[i] = str2[j];
    }
    str1[i] = '\0';
}

int main(){
    char str1[100], str2[100];
    printf("Enter the first string: ");
    gets(str1);
    printf("Enter the second string: ");
    gets(str2);
    stringConcat(str1, str2);
    printf("The concatenated string is: %s", str1);
    return 0;
}