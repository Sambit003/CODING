#include<stdio.h>
#include<string.h>
#define SIZE 50

int main(){
    char str[SIZE];
    int i=0;

    printf("\n\tEnter a string: ");
    gets(str);

    i= strlen(str);

    printf("\n\tThe length of the string is: %d", i);

    return 0;
}