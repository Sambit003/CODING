//Write a C program to find length of a string using user defined function and pointer.

#include <stdio.h>
#define SIZE 50
int lengthCalc(char *str){
    int i=0;
    while(str[i]!='\0'){
        i++;
    }
    return i;
}

int main(){
    char str[SIZE];
    
    printf("\n\tEnter a string: ");
    gets(str);

    printf("\n\tThe length of the string is: %d", lengthCalc(str));
    return 0;
}