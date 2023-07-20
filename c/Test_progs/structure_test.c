#include<stdio.h>
#include<stdlib.h>
    struct {
        char name[60], addrs[100]; int contact,roll,admdt;
    } stdu1;
int main()
{
    printf("\n\tEnter the name of the student : ");
    gets(stdu1.name);
    printf("\n\tEnter address : ");
    gets(stdu1.addrs);
    printf("\n\tEnter contact no. , roll , admission date :");
    scanf("%d%d%d",&stdu1.contact,&stdu1.roll,&stdu1.admdt);
    printf("\n\t%c\n\t%c\n\t%d\n\t%d\n\t%d",stdu1.name,stdu1.addrs,stdu1.contact,stdu1.roll,stdu1.admdt);
    return(printf("\n\tExecuted Successfully"));
}
