#include <stdio.h>

int main() {
    int num1, num2, gcd, lcm;

    printf("Enter two positive integers: ");
    scanf("%d %d", &num1, &num2);

    int a = num1, b = num2;

    while(b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }

    gcd = a;
    lcm = (num1 * num2) / gcd;

    printf("GCD of the given numbers is: %d\n", gcd);
    printf("LCM of the given numbers is: %d\n", lcm);

    return 0;
}