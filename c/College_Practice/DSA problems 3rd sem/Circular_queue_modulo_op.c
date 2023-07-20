#include <stdio.h>
#define max 5

int queue[max];
int front=-1;
int rear=-1;

void enqueue(int element)
{

    if((rear+1)%max==front)
    {
        printf("Queue is overflow..");
        return;
    }

    if(front==-1 && rear==-1)
    {
        front=0;
        rear=0;

    }
    else
    {
        rear=(rear+1)%max;
    }

    queue[rear]=element;

}


void dequeue()
{
    if((front==-1))
    {
        printf("\nQueue is underflow..");
        return ;
    }

     printf("\nThe dequeued element is %d", queue[front]);

    if(front==rear)
    {
    front=-1;
    rear=-1;
    }
    else
    {
        front=(front+1)%max;
    }

}


void display()
{
    int i=front;
    if(front==-1)
    {
        printf("\n Queue is empty..");
    }
    else
    {
        printf("\nElements in a Queue are :");
        for (i = front; i != rear; i = (i + 1) % max)
        {
            printf("%d,", queue[i]);
        }
        printf("%d,", queue[i]);

    }
}
int main()
{
    int choice=1,x;

    while(choice<4 && choice!=0)
    {
    printf("\n\nPress 1 : Insert ");
    printf("\nPress 2 : Delete ");
    printf("\nPress 3 : Display ");
    printf("\n\nEnter your choice  : ");
    scanf("%d", &choice);

    switch(choice)
    {

        case 1:
            printf("\nEnter the element which is to be inserted :: ");
            scanf("%d", &x);
            enqueue(x);
            break;
        case 2:
            dequeue();
            break;
        case 3:
            display();
    }}
    return 0;
}
