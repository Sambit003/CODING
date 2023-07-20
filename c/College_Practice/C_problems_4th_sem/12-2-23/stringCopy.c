//Write a C program to copy one string to another using user defined function.

#include <stdio.h>
#define SIZE 50

void strCopy(char *str1){
    char str2[SIZE];
    int i=0;
    while(str1[i]!='\0'){
        str2[i] = str1[i];
        i++;
    }
    str2[i] = '\0';
    printf("\n\tThe copied string is: %s", str2);
}

int main(){
    char str1[SIZE];
    printf("\n\tEnter a string: ");
    gets(str1);

    strCopy(str1);
    
    return 0;
}