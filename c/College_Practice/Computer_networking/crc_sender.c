// WAP in C to implement Cycle Redundancy Check (CRC) error detection algorithm.

/*
    Step 1: Take the data bit from user in binary form. and take the divisor in binary form.
    Step 2: Append the data bit with n-1 zeros. Set the data bit as new dividend.
    Step 3: Divide the dividend with the divisor and get the remainder.
    Step 4: Append the remainder with the data input by the user at step 1 and set it as code bit which is to be transmitted.
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// Function to perform CRC
char* CRC(char* data, char* key) {
    int l_key = strlen(key);
    int l_data = strlen(data);
    char* dividend = (char*)calloc((l_data+l_key-1),sizeof(char));
    char* remainder = (char*)calloc((l_key-1),sizeof(char));

    // Copying the value of data to dividend
    strcpy(dividend, data);

    // Append 0's at the end of data
    for(int i=0; i<l_key-1; i++)
        dividend[l_data+i] = '0';

    // Put null character at the end of data
    dividend[l_data+l_key-1] = '\0';

    //The new dividend
    printf("\n\tThe new dividend is: %s", dividend);

    // Perform XOR operation on the data
    for(int i=0; i<l_data; i++) {
        if(dividend[i] == '1') { 
            for(int j=0; j<l_key; j++)
                dividend[i+j] = (dividend[i+j] == key[j])? '0' : '1'; // XOR operation
        }
    }
    
    // The remainder
    for(int i=0; i<l_key-1; i++)
        remainder[i] = dividend[l_data+i];
    
    free(dividend); dividend = NULL;
    return remainder;
}

int main(){
    int data_size, key_size;
    
    SET_SIZE: printf("Enter the size of data word and key: ");
    scanf("%d %d", &data_size, &key_size);

    char* data = (char*)calloc((data_size+key_size-1),sizeof(char));
    char* key = (char*)calloc(key_size,sizeof(char));
    if (data == NULL || key == NULL) {
        printf("Memory not allocated.\n");
        data = NULL;
        key = NULL;
        goto SET_SIZE;
    }
    else{
        printf("\n\tMemory allocated successfully.\n");
        printf("\n\tEnter the data[in binary form]: ");
        fflush(stdin);
        gets(data);
        printf("\n\tEnter the key [divisor]: ");
        gets(key);

        char* code = CRC(data, key);
        printf("\n\tThe code is: %s\n", strcat(data, code));

        free(data); data = NULL;
        free(key); key = NULL;
        free(code); code = NULL;
    }
    return 0;
}