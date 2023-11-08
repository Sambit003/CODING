#include<stdio.h>
#include<stdlib.h>
typedef struct node{
    int data;
    struct node *next;
}nd;

void InsertBegin(nd **head){
    nd *ptr; int item;
    ptr=(nd *) malloc(sizeof(nd *));
    if(ptr==NULL)   printf("\n\tUNABLE TO ALLOCATE MEMORY");
    else{
        printf("\n\tEnter the data to insert: ");
        scanf("%d",&item);
        ptr->data=item;
        ptr->next= *head;
        *head = ptr;
        printf("\n\tDATA INSERTED SUCCESSFULLY");
    }
}


void DeletePrev(nd **head){
    nd *ptr=*head; int SrchItem;
    printf("\n\tEnter the value: ");
    scanf("%d",&SrchItem);
    if(ptr->next->data==SrchItem){
        printf("\n\tcannot delete the previous as it is head");
    }
    else{
        while(ptr->next->next->data!=SrchItem){
            ptr=ptr->next;
        }
        ptr->next=ptr->next->next;
        free(ptr);
        printf("\n\tPrevious Node deleted successfully");
    }
}

void DeleteBeginning(nd **head){
    nd *ptr;
    if(*head==NULL) printf("\n\tLIST IS EMPTY");
    else{
        ptr= *head;
        *head= ptr->next;
        free(ptr);
        printf("\n\tDeleted Successfully");
    }
}

void DisplayList(nd **head){
    nd *ptr=*head;
    printf("\n\t==========LINKED LIST===========\n");
    if(ptr==NULL)   printf("\n\tNo data to print");
    else{
        while(ptr!=NULL)
        {
            printf("\t%d",ptr->data);
            ptr=ptr->next;
        }
    }
}

int main(){
    nd *head=NULL; int choice;
    while(1)
    {
        printf("\n\n\t===========LINKED LIST AND OPERATIONS==========\n\t1. Insert\n\t2. Display\n\t3. Delete from beginning\n\t4. Delete the previous\n\t5. Exit\n\n\tEnter the choice (numerics only): ");
        scanf("%d",&choice);
        switch(choice){
        case 1:
            InsertBegin(&head);
            break;
        case 2:
            DisplayList(&head);
            break;
        case 3:
            DeleteBeginning(&head);
            break;
        case 4:
            DeletePrev(&head);
            break;
        case 5:
            exit(0);
        default:  printf("\n\tEnter valid choice");
        }
    }
    return 0;
}