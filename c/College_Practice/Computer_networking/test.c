#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to perform XOR operation
char XOR(char a, char b) {
    return (a == b) ? '0' : '1';
}

// Function to perform XOR division and return the remainder
char* XORDivision(char* dividend, char* divisor) {
    int dividendLength = strlen(dividend);
    int divisorLength = strlen(divisor);
    char* result = (char*)malloc(dividendLength + 1); // Allocate memory for the result

    // Copy the dividend to the result initially
    strcpy(result, dividend);

    for (int i = 0; i <= dividendLength - divisorLength; i++) {
        if (result[i] == '1') {
            for (int j = 0; j < divisorLength; j++) {
                result[i + j] = XOR(result[i + j], divisor[j]);
            }
        }
    }

    // Calculate the remainder (it's the remaining part of 'result')
    char* remainder = result + (dividendLength - divisorLength + 1);

    return remainder;
}

int main() {
    char dividend[] = "10110000";
    char divisor[] = "1001";

    char* remainder = XORDivision(dividend, divisor);

    printf("Dividend: %s\n", dividend);
    printf("Divisor:  %s\n", divisor);
    printf("Remainder: %s\n", remainder);

    free(remainder); // Free dynamically allocated memory

    return 0;
}
