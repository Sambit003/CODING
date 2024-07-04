#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to perform CRC on received data
int CRCReceiver(char* receivedData, char* key) {
    int l_key = strlen(key);
    int l_receivedData = strlen(receivedData);

    // Perform XOR operation on the received data
    for (int i = 0; i < l_receivedData; i++) {
        if (receivedData[i] == '1') {
            for (int j = 0; j < l_key; j++)
                receivedData[i + j] = (receivedData[i + j] == key[j]) ? '0' : '1'; // XOR operation
        }
    }

    // Check if the remainder is all zeros
    for (int i = l_receivedData; i < l_receivedData + l_key - 1; i++) {
        if (receivedData[i] == '1') {
            return 0; // Error detected
        }
    }

    return 1; // No error detected
}

int main() {
    int receivedDataSize, keySize;

    printf("Enter the size of received data word and key: ");
    scanf("%d %d", &receivedDataSize, &keySize);

    char* receivedData = (char*)calloc((receivedDataSize + keySize - 1)+1, sizeof(char));
    char* key = (char*)calloc(keySize+1, sizeof(char));

    if (receivedData == NULL || key == NULL) {
        printf("Memory not allocated.\n");
        return 1;
    } else {
        printf("\nMemory allocated successfully.\n");
        printf("\nEnter the received data [in binary form]: ");
        fflush(stdin);
        gets(receivedData);
        printf("\nEnter the key [divisor]: ");
        gets(key);

        int errorDetected = CRCReceiver(receivedData, key);

        if (errorDetected) {
            printf("\nNo error detected. Received data is correct.\n");
        } else {
            printf("\nError detected in received data.\n");
        }

        free(receivedData);
        free(key);
        return 0;
    }
}
