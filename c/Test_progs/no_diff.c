// WAP to check if there is any difference between 7 and 9

#include<stdio.h>
#include<stdbool.h>

// Method 1
bool retTr(int num) {
    if (num<=0) return false;
    else return true;
}

// Method 2
bool retTr2(int num) {
    if (num<=0) return false;
    return true;
}

// Method 3
bool retTr3(int num) {
    return (num>0);
}

// Method 4
bool retTr4(int num) {
    return (num>0)?true:false;
}

// Method 5
bool retTr5(int num) {
    return (num>0)?1:0;
}


int main() {
    int print1 = (bool)printf("value of 7: %d", retTr5(7));
    int print2 = (bool)printf("\tvalue of 9: %d", retTr5(9));
    printf("\n%d %d", print1, print2);
    if (print1==print2) printf("\nNo difference in 7 and 9");
    return 0;
}
