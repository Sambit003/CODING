// wap in C to generate parity bit for a given data word

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

bool check_parity(char *data){
    int count=0;
    for(int i=0; i<strlen(data); i++){
        if(data[i] == '1')
            count++;
    }
    if(count%2 == 0)
        return true;
    else
        return false;
}

int main(){
    char *data=NULL; int n, count=0;
    printf("\n\tEnter the number of bits in data word [in binary]: ");
    scanf("%d", &n);

    data = (char *)calloc(n, sizeof(char));

    printf("\n\tEnter the data word: ");
    fflush(stdin);
    gets(data);

    if(check_parity(data)){
        char choice;
        printf("\n\t1. Even Parity\n\t2. Odd Parity\n\tEnter your choice: ");
        scanf(" %c", &choice);
        switch(choice){
            case '1':
                data[n] = '0'; // even parity
                break;
            case '2':
                data[n] = '1'; // odd parity
                break;
            default:
                printf("\n\tInvalid choice!");
                exit(0);
        }
    }
    else{
        char choice;
        printf("\n\t1. Even Parity\n\t2. Odd Parity\n\tEnter your choice: ");
        scanf(" %c", &choice);
        switch(choice){
            case '1':
                data[n] = '1'; // even parity
                break;
            case '2':
                data[n] = '0'; // odd parity
                break;
            default:
                printf("\n\tInvalid choice!");
                exit(0);
        }
    }

    printf("\n\tThe data word with parity bit is: ");
    puts(data);

    free(data);
    data = NULL;
    return 0;
}