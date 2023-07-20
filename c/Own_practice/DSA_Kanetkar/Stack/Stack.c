#include<stdio.h>
#include<stdlib.h>
#define DEFAULT_VALUE NULL
typedef struct node{
    int data; struct node *link;
}StackNode;

/*Basic stack functionalities*/
void push(StackNode **, int);
int pop(StackNode **);
void dealloc_stack_mem(StackNode **);
//void peek(StackNode **);

/*Main implementation*/
int main(){
    StackNode *s=NULL;  int n,choice=NULL;
    return 0;   
}

/*adds a new node at beginning of linked list*/
void push(StackNode **top, int item){
    StackNode *temp;
    temp=(StackNode *)malloc(sizeof(StackNode));

    if(temp==NULL)  printf("\n\tSTACK IS FULL");

    temp->data=item;
    temp->link=*top;
    *top=temp;
}

/*Deletes a node from the beginning of linked list*/
int pop(StackNode **top){
    StackNode *temp;

    if(*top==NULL){
        printf("\n\tSTACK IS EMPTY");
        return NULL;
    }

    temp=*top;
    return temp->data;
    *top=(*top)->link;

    free(temp);
}

/*Deallocates memory*/
void dealloc_stack_mem(StackNode **top){
    StackNode *temp;

    if(*top==NULL)  return;

    while(*top!=NULL){
        temp=*top;
        *top=(*top)->link;
        free(temp);
    }
}