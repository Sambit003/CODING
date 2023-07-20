// 8. Write a C Program to read an array of names and to set them in alphabetical order.

#include <stdio.h>
#include <string.h>

int main(){
    int n;
    printf("Enter the number of names: ");
    scanf("%d", &n);
    char names[n][100];
    for(int i = 0; i < n; i++){
        printf("Enter the name %d: ", i+1);
        scanf("%s", names[i]);
    }
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            if(strcmp(names[i], names[j]) > 0){
                char temp[100];
                strcpy(temp, names[i]);
                strcpy(names[i], names[j]);
                strcpy(names[j], temp);
            }
        }
    }
    printf("The names in alphabetical order are: ");
    for(int i = 0; i < n; i++){
        printf("\n\t%s", names[i]);
    }
    return 0;
}