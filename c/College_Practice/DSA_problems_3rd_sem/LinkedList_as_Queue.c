//Write a program to implement linked list as queue

#include <stdio.h>
#include <stdlib.h>

//Structure of a node
typedef struct node{
    int data;
    struct node *next;
}node;

//Global variable
node *head = NULL;

//Function to insert a node at the end of the queue
void enqueue(int data){
    node *new_node = (node *)malloc(sizeof(node));
    new_node->data = data;
    new_node->next = NULL;
    if (head == NULL){
        head = new_node;
    }
    else{
        node *temp = head;
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

//Function to delete a node from the front of the queue
void dequeue(){
    node *temp = head;
    head = head->next;
    free(temp);
}

//Function to display the queue
void display(){
    node *temp = head;
    while (temp != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

//Main function
int main(){
    enqueue(1);
    enqueue(2);
    enqueue(3);
    enqueue(4);
    enqueue(5);
    display();
    dequeue();
    display();
    return 0;
}