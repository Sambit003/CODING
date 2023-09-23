// WAP in C to implement Tower of Hanoi problem using recursion.

#include<stdio.h>
#include<stdlib.h>

void tower_of_hanoi(int n, char beg, char aux, char dest){
    if (n<=0) printf("\n\tIllegal Array");
    else if (n==1){
        printf("\n\tMoving disk from %c to %c", beg, dest);
    }
    else{
        tower_of_hanoi(n-1,beg,dest,aux);
        tower_of_hanoi(1,beg,aux,dest);
        tower_of_hanoi(n-1,aux,beg,dest);
    }
}

int main(){
    int n;
    NO_OF_DISKS: printf("\n\tEnter the number of disks: ");
    scanf("%d",&n);

    if(n<=0){
        printf("\n\tNos of disks can't be negarive or equal to zero::::Try again!!\n\tPress any key to continue:");
        fflush(stdin);
        getch();
        system("cls");
        goto NO_OF_DISKS;
    }
    else{
        printf("\n\t:_:_:_:Steps:_:_:_:");
        tower_of_hanoi(n,'A','B','C');
    }
    return 0;
}