// WAP in C to implement error detection mechanism using checksum method for sender side.

#include <stdio.h>
#include <string.h>

int main() {
  char data[100], zero[100];
  int s, z, i, j, datal, c, sum[100], t, k;
  
  printf("\n\tEnter the data to be sent: ");
  scanf("%s", data);

  datal = strlen(data);

  printf("\n\tEnter the segment length: ");
  scanf("%d", &s);

  z = (s - (datal % s)) % s;

  for (i = 0; i < z; i++) {
    zero[i] = '0';
  }

  zero[i] = '\0';

  strcat(zero, data);
  strcpy(data, zero);

  for (i = 0; i < s; i++) {
    sum[i] = 0;
  }

  for (i = datal; i > 0; i = i - s) {
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

  // Update the original data with the checksum
  for (i = 0; i < s; i++) {
    if (sum[i] == 1) sum[i] = 0;
    else sum[i] = 1;

    data[datal + i] = sum[i] + '0';
  }

  data[datal + s] = '\0'; // Ensure null-terminated string

  printf("\n\tChecksum: ");
  for (i = 0; i < s; i++) {
    printf("%d", sum[i]);
  }

  printf("\n\tThe codeword: %s\n", data);

  return 0;
}
