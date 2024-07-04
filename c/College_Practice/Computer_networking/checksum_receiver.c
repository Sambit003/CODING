#include <stdio.h>
#include <string.h>

int main() {
    char data[100], zero[100];
    int s, z, i, j, datal, c, sum[100], t, k, flag = 1;

    printf("\n\tEnter the codeword: ");
    scanf("%s", data);

    datal = strlen(data);

    printf("\n\tEnter the segment length: ");
    scanf("%d", &s);

    for (i = 0; i < s; i++) {
        sum[i] = '0';
    }

    for (i = datal; i > 0; i--) {
        c = 0;
        k = s - 1;
        for (j = i - 1; j >= i - s; j--) {
            t = sum[k] + (data[j] - '0') + c;
            sum[k] = t % 2;
            c = t / 2;
            k--;
        }

        if (c == 1) {
            for (j = s - 1; j >= 0; j--) {
                t = sum[j] + c;
                sum[j] = t % 2;
                c = t / 2;
            }
        }
    }

    for (i = 0; i < s; i++) {
        if (sum[i] == (data[datal - s + i] - '0')) {
            flag = 0;
            break;
        }
    }

    if (flag == 0) {
        printf("\n\tThe codeword is correct.\n");
        data[datal - s] = '\0';
        printf("\n\tThe data sent is: %s\n", data);
    } else {
        printf("\n\tThe codeword is incorrect.\n");
    }

    return 0;
}
