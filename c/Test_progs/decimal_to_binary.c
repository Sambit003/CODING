//WAP to add two numbers and show the result in binary form

#include<stdio.h>

int main(){
    int a=10,b=20,c;
    c=a+b;
    printf("The sum of %d and %d is %d\n",a,b,c);
    
    //binary conversion algorithm : Brute force
    for (int i = 31; i >= 0; i--) // This loop is for 32 bit system
    {
        int k=c>>i; // Right shift by i bits.
        /*
        Why this left shift is required?
        Ans: Because we are checking the MSB first. So, we need to shift the bits to the right.
        */
        if(k&1){ // Bitwise AND operation. Result will be 1 if both bits are 1.
            printf("1"); // If the result is 1, then print 1.
        }
        else{
            printf("0"); // If the result is 0, then print 0.
        }
    }
    printf("\n");
    return 0;
}
