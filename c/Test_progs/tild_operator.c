#include <stdio.h>
int main()
{
    int a = 11;
    int b = ~a;
    printf("%d", b);
}

/* 
How does the tilde operator work in C?
The tilde operator is a bitwise operator. It inverts the bits of its operand.

For example, if a is 11, then ~a will be -12. This is because the binary representation of 11 is 00001011.
The binary representation of -12 is 11110100. The tilde operator inverts the bits of its operand.
Expected output: 4
Compiler returns -12
*/