/*
    A pointer in C++ is used to share a memory address among different contexts (primarily functions). They are used whenever a function needs to modify the content of a variable, but it does not have ownership.

In order to access the memory address of a variable, , prepend it with  sign. For example, &val returns the memory address of .

This memory address is assigned to a pointer and can be shared among functions. For example, int*p = &val assigns the memory address of val to pointer p. To access the content of the memory pointed to, prepend the variable name with a*. For example, *p will return the value stored in  and any modification to it will be performed on .

void increment(int *v) {
    (*v)++;
}

int main() {
    int a;
    scanf("%d", &a);
    increment(&a);
    printf("%d", a);
    return 0;
}  
Function Description

Complete the update function in the editor below.

update has the following parameters:

int *a: an integer
int *b: an integer
Returns
a' = a+b
b' = |a-b|

The function is declared with a void return type, so there is no value to return. Modify the values in memory so that  contains their sum and  contains their absoluted difference.


Input Format

Input will contain two integers, a and b, separated by a newline.

Sample Input
4
5

Sample Output
9
1

Explanation
a' = 4+5 = 9
b' = |4-5| = 1

Code:
#include <stdio.h>

void update(int *a,int *b) {
    // Complete this function    
}

int main() {
    int a, b;
    int *pa = &a, *pb = &b;
    
    scanf("%d %d", &a, &b);
    update(pa, pb);
    printf("%d\n%d", a, b);

    return 0;
}
*/


#include<stdio.h>

void update(int *a, int *b){
    int temp = *a;
    *a = *a + *b;
    *b = temp - *b;
    if(*b < 0){
        *b = *b * -1; // Dereferencing the pointer 'b' and multiplying the value it points to by '-1'. This changes the sign of the value that 'b' points to.
    }
}

int main() {
    int a,b;
    int *pa = &a, *pb = &b;

    scanf("%d %d", &a, &b);
    update(pa,pb);
    printf("%d\n%d", a,b);

    return 0;
}
