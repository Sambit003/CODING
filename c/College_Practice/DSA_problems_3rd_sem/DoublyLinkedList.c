#include<stdio.h>
#include<stdlib.h>
typedef struct node{
    int data;
    struct node *next;
    struct node *prev;
}Node;

void InitNode(Node *ptr){
    ptr->data=0;
    ptr->next=NULL;
    ptr->prev=NULL;
}

void CreateNode(Node *ptr){
    int n;
    printf("\n\tEnter data: ");
    scanf("%d",&n);
    ptr->data=n;
}

void Display(Node *ptr){
    while(ptr!=NULL){
        printf("\t%d",ptr->data);
        ptr=ptr->next;
    }
}

void InsertAtBeg(Node **ptr){
    Node *temp;
    temp=(Node *)malloc(sizeof(Node));
    CreateNode(temp);
    temp->next=*ptr;
    *ptr=temp;
}

void InsertAtEnd(Node **ptr){
    Node *temp, *temp1;
    temp=(Node *)malloc(sizeof(Node));
    CreateNode(temp);
    temp1=*ptr;
    while(temp1->next!=NULL)    temp1=temp1->next;
    temp1->next=temp;
    temp->prev=temp1;
}

void InsertAtPos(Node **ptr){
    Node *temp, *temp1;
    int pos, count=1;
    temp=(Node *)malloc(sizeof(Node));
    CreateNode(temp);
    temp1=*ptr;
    printf("\n\tEnter position: ");
    scanf("%d",&pos);
    while(count<pos-1){
        temp1=temp1->next;
        count++;
    }
    temp->next=temp1->next;
    temp1->next=temp;
    temp->prev=temp1;
    temp->next->prev=temp;
}

void DeleteAtBeg(Node **ptr){
    Node *temp;
    temp=*ptr;
    *ptr=temp->next;
    free(temp);
}

void DeleteAtEnd(Node **ptr){
    Node *temp, *temp1;
    temp=*ptr;
    while(temp->next!=NULL){
        temp1=temp;
        temp=temp->next;
    }
    temp1->next=NULL;
    free(temp);
}

void DeleteAtPos(Node **ptr){
    Node *temp, *temp1;
    int pos, count=1;
    temp=*ptr;
    printf("\n\tEnter position: ");
    scanf("%d",&pos);
    while(count<pos-1){
        temp=temp->next;
        count++;
    }
    temp1=temp->next;
    temp->next=temp1->next;
    temp1->next->prev=temp;
    free(temp1);
}

int main(){
    Node *head;
    int choice;
    head=(Node *)malloc(sizeof(Node));
    InitNode(head);
    do{
        printf("\n\t1. Insert at beginning");
        printf("\n\t2. Insert at end");
        printf("\n\t3. Insert at position");
        printf("\n\t4. Delete at beginning");
        printf("\n\t5. Delete at end");
        printf("\n\t6. Delete at position");
        printf("\n\t7. Display");
        printf("\n\t8. Exit");
        printf("\n\tEnter choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1: InsertAtBeg(&head);
                    break;
            case 2: InsertAtEnd(&head);
                    break;
            case 3: InsertAtPos(&head);
                    break;
            case 4: DeleteAtBeg(&head);
                    break;
            case 5: DeleteAtEnd(&head);
                    break;
            case 6: DeleteAtPos(&head);
                    break;
            case 7: Display(head);
                    break;
            case 8: exit(0);
            default: printf("\n\tInvalid choice");
        }
    }while(choice!=8);
    return 0;
}
