//Write a C program to reverse a string using pointer.

#include <stdio.h>
#define SIZE 50

void reverse(char *str){
    char temp;
    int i=0;
    while(str[i]!='\0'){
        i++;
    }
    for(int j=0;j<i/2;j++){
        temp = str[j];
        str[j] = str[i-j-1];
        str[i-j-1] = temp;
    }
}

int main(){
    char str[SIZE];

    printf("\n\tEnter a string: ");
    gets(str);

    reverse(str);
    printf("\n\tThe reversed string is: %s", str);
    
    return 0;
}