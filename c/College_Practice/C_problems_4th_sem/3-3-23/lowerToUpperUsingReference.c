// 4. Write a C program to convert lowercase string to uppercase string and vice versa using call by reference.

#include <stdio.h>
#include <string.h>

// Function to convert lowercase string to uppercase string
void lowerToUpper(char* str){
    for(int i = 0; i < strlen(str); i++){
        if(str[i] >= 'a' && str[i] <= 'z'){
            str[i] -= 32;
        }
        else if(str[i] >= 'A' && str[i] <= 'Z'){
            str[i] += 32;
        }
        else    continue;
    }
}


int main(){
    char str[100];
    printf("Enter a string: ");
    gets(str);
    lowerToUpper(str);
    printf("The string in uppercase is: %s", str);
    return 0;
}