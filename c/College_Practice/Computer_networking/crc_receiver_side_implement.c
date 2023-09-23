#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int CRC_check(char* data, char* key){
    int data_size = strlen(data);
    int key_size = strlen(key);

    char* remainder = (char*) malloc((data_size + 1) * sizeof(char));
    strcpy(remainder, data);

    for (int i = 0; i < data_size - key_size + 1; i++){
        if (remainder[i] == '1'){
            for (int j = 0; j < key_size; j++){
                if (remainder[i+j] == key[j])
                    remainder[i+j] = '0';
                else
                    remainder[i+j] = '1';
            }
        }
    }

    remainder[data_size] = '\0';

    printf("\nRemainder: %s\n", remainder);

    for (int i = 0; i < data_size; i++)
        if (remainder[i] == '1'){
            free(remainder);
            return 0;
        }

    free(remainder);
    return 1;
}

int verify_CRC(char* received_data, char* CRC_value, char* key){
    int data_size = strlen(received_data);
    int CRC_size = strlen(CRC_value);

    char* data = (char*) malloc((data_size + CRC_size + 1) * sizeof(char));
    strcpy(data, received_data);

    for (int i = 0; i < CRC_size; i++){
        data[data_size+i] = CRC_value[i];
    }
    data[data_size+CRC_size] = '\0';

    int result = CRC_check(data, key);

    free(data);
    return result;
}

int main(){
    int data_size, key_size, CRC_size;
    SET_SIZE: printf("\n\tEnter the size of data, key, crc: ");
    scanf("%d %d %d", &data_size, &key_size, &CRC_size);
    int choice;

    char *data = (char *) calloc(data_size + 1, sizeof(char));
    char *key = (char *) calloc(key_size + 1, sizeof(char));
    char *CRC = (char *) calloc(CRC_size + 1, sizeof(char));

    if (data == NULL || key == NULL || CRC == NULL){
        printf("\n\tMemory allocation failed!\n");
        free(data); data = NULL;
        free(key); key = NULL;
        free(CRC); CRC = NULL;
        goto SET_SIZE;
    }
    else{
        printf("\n\tMemory allocation successful!\n");
        printf("\n\tEnter the data: ");
        scanf("%s", data);

        printf("\nEnter the key: ");
        scanf("%s", key);

        CRC_check(data, key);

        printf("\n\tDo you want to simulate error in transmission?\n1. Yes\n2. No\nEnter your choice: ");
        scanf("%d", &choice);

        if (choice == 1){
            int error_bit;
            printf("\n\tEnter the bit position to flip (0-indexed): ");
            scanf("%d", &error_bit);

            if (data[error_bit] == '0')
                data[error_bit] = '1';
            else
                data[error_bit] = '0';

            printf("\n\tData after introducing error: %s\n", data);
        }

        printf("\n\tEnter the received data: ");
        scanf("%s", data);

        printf("\n\tEnter the transmitted CRC value: ");
        scanf("%s", CRC);

        int result = verify_CRC(data, CRC, key);

        if (result == 1)
            printf("\n\tData is valid and has not been corrupted during transmission.\n");
        else
            printf("\n\tData is corrupted and should be discarded.\n");

        free(data); data = NULL;
        free(key); key = NULL;
        free(CRC); CRC = NULL;
    }
    return 0;
}