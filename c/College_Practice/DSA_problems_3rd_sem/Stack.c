// Write a program to implement stack by array
#include<stdio.h>
#include<stdlib.h>
#define MAX 5
int stack[MAX],top=-1;
void push();
void pop();
void display();
void main()
{
    int ch;
    while(1)
    {
        printf("1.Push\n2.Pop\n3.Display\n4.Exit\n");
        printf("Enter your choice:");
        scanf("%d",&ch);
        switch (ch)
        {
        case 1: 
            push();
            break;
        case 2: 
            pop();
            break;
        case 3:
            display();
            break;
        case 4:
            exit(0);
        default:    printf("\n\tWRONG CHOICE");
        }
    }
}

void push()
{
    int item;
    if(top==MAX-1)
    {
        printf("Stack is full");
    }
    else
    {
        printf("Enter the element to be pushed:");
        scanf("%d",&item);
        top=top+1;
        stack[top]=item;
    }
}

void pop()
{
    if(top==-1)
    {
        printf("Stack is empty");
    }
    else
    {
        printf("The popped element is %d",stack[top]);
        top=top-1;
    }
}

void display()
{
    int i;
    if(top==-1)
    {
        printf("Stack is empty");
    }
    else
    {
        printf("The elements in the stack are:");
        for(i=top;i>=0;i--)
        {
            printf("%d\t",stack[i]);
        }
    }
}