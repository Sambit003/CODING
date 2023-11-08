//Write a program in C to implement the full Linked List operations

#include <stdio.h>
#include <stdlib.h>
typedef struct node{
    int data;
    struct node *next;
}node;
node *head = NULL;
void create(){
    node *new_node, *temp;
    int choice = 1;
    while (choice){
        new_node = (node *)malloc(sizeof(node));
        printf("Enter the data: ");
        scanf("%d", &new_node->data);
        new_node->next = NULL;
        if (head == NULL)   head = new_node;
        else{
            temp = head;
            while (temp->next != NULL)  temp = temp->next;
            temp->next = new_node;
        }
        printf("Do you want to continue? (1/0): ");
        scanf("%d", &choice);
    }
}
void insert(int data){
    node *new_node = (node *)malloc(sizeof(node));
    new_node->data = data;
    new_node->next = head;
    head = new_node;
}
void insert_after(int data, int after){
    node *new_node = (node *)malloc(sizeof(node));
    new_node->data = data;
    node *temp = head;
    while (temp->data != after) temp = temp->next;
    new_node->next = temp->next;
    temp->next = new_node;
}
void insert_before(int data, int before){
    node *new_node = (node *)malloc(sizeof(node));
    new_node->data = data;
    node *temp = head;
    while (temp->next->data != before) temp = temp->next;
    new_node->next = temp->next;
    temp->next = new_node;
}
void insert_end(int data){
    node *new_node = (node *)malloc(sizeof(node));
    new_node->data = data;
    new_node->next = NULL;
    node *temp = head;
    while (temp->next != NULL)  temp = temp->next;
    temp->next = new_node;
}
void delete_beg(){
    node *temp = head;
    head = head->next;
    free(temp);
}
void delete_end(){
    node *temp = head;
    while (temp->next->next != NULL)    temp = temp->next;
    free(temp->next);
    temp->next = NULL;
}
void delete_after(int after){
    node *temp = head;
    while (temp->data != after) temp = temp->next;
    node *temp2 = temp->next;
    temp->next = temp->next->next;
    free(temp2);
}
void delete_before(int before){
    node *temp = head;
    while (temp->next->next->data != before) temp = temp->next;
    node *temp2 = temp->next;
    temp->next = temp->next->next;
    free(temp2);
}
void delete_node(int data){
    node *temp = head;
    while (temp->next->data != data)    temp = temp->next;
    node *temp2 = temp->next;
    temp->next = temp->next->next;
    free(temp2);
}
void display(){
    node *temp = head;
    printf("\n\t========LINKE LIST========\n");
    while (temp != NULL){
        printf("%d\t", temp->data);
        temp = temp->next;
    }
    printf("\n\t==========================\n");
}
int main(){
    int choice, data, after, before;
    while (1){
        printf("\n\t\tMENU");
        printf("\n\t1. Create Linked List");
        printf("\n\t2. Insert at beginning");
        printf("\n\t3. Insert after a node");
        printf("\n\t4. Insert before a node");
        printf("\n\t5. Insert at end");
        printf("\n\t6. Delete from beginning");
        printf("\n\t7. Delete from end");
        printf("\n\t8. Delete after a node");
        printf("\n\t9. Delete before a node");
        printf("\n\t10. Delete a node");
        printf("\n\t11. Display");
        printf("\n\t12. Exit");
        printf("\n\tEnter your choice: ");
        scanf("%d", &choice);
        switch (choice){
            case 1: create(); break;
            case 2: printf("Enter the data: ");
                    scanf("%d", &data);
                    insert(data); break;
            case 3: printf("Enter the data: ");
                    scanf("%d", &data);
                    printf("Enter the node after which you want to insert: ");
                    scanf("%d", &after);
                    insert_after(data, after); break;
            case 4: printf("Enter the data: ");
                    scanf("%d", &data);
                    printf("Enter the node before which you want to insert: ");
                    scanf("%d", &before);
                    insert_before(data, before); break;
            case 5: printf("Enter the data: ");
                    scanf("%d", &data);
                    insert_end(data); break;
            case 6: delete_beg(); break;
            case 7: delete_end(); break;
            case 8: printf("Enter the node after which you want to delete: ");
                    scanf("%d", &after);
                    delete_after(after); break;
            case 9: printf("Enter the node before which you want to delete: ");
                    scanf("%d", &before);
                    delete_before(before); break;
            case 10: printf("Enter the node you want to delete: ");
                    scanf("%d", &data);
                    delete_node(data); break;
            case 11: display(); break;
            case 12: exit(0);
            default: printf("Invalid choice!");
        }
    }
    return 0;
}