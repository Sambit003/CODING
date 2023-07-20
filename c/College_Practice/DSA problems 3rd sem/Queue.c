#include<stdio.h>
#include<stdlib.h>
#define MAX 5
int queue[MAX],front=-1,rear=-1;
void insert();
void delete();
void display();
void main(){
    int ch;
    while(1){
        printf("\n\t1.Insert\n\t2.Delete\n\t3.Display\n\t4.Exit\n");
        printf("\n\tEnter your choice:");
        scanf("%d",&ch);
        switch (ch)
        {
            case 1: 
                insert();
                break;
            case 2:
                delete();
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

void insert(){
    int item;
    if(rear==MAX-1){
        printf("\n\tQueue is full");
    }
    else{
        printf("\n\tEnter the element to be inserted:");
        scanf("%d",&item);
        if(front==-1){
            front=0;
        }
        rear=rear+1;
        queue[rear]=item;
    }
}

void delete(){
    if(front==-1||front>rear){
        printf("\n\tQueue is empty");
    }
    else{
        printf("\n\tThe deleted element is %d",queue[front]);
        front=front+1;
    }
}

void display(){
    int i;
    if(front==-1){
        printf("\n\tQueue is empty");
    }
    else{
        printf("\n\tThe elements of the queue are:");
        for(i=front;i<=rear;i++){
            printf("%d\t",queue[i]);
        }
    }
}