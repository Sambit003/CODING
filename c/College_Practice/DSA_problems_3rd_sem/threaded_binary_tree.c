/*
    Why the threaded binary tree is used?
    Ans: The threaded binary tree is used to reduce the number of null pointers in the tree.
    The null pointers are replaced by the pointers to the inorder successor or predecessor.
    It saves the space and time required to find the inorder successor or predecessor.
    The inorder traversal of the threaded binary tree is more efficient than the normal binary tree.
    
    For postorder and preorder traversal, the threaded binary tree is not efficient. Why?
    Ans: Because the postorder and preorder traversal requires the left and right child of the node.
    And in the threaded binary tree, the left and right child of the node is replaced by the inorder 
    successor or predecessor, efficient postorder and preorder traversals in a threaded binary tree 
    would typically involve using additional data structures, such as stacks or queues, to maintain 
    the required order of node access, which can introduce complexity and overhead.
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

enum boolean {
    link, thread
};

typedef struct node {
    enum boolean ltag, rtag;
    tbt_node *left_child, *right_child;
    int data;
} tbt_node;

// This block is for function prototyping
void init(tbt_node **);
void insert(tbt_node **, int);
void delete(tbt_node **, int);
void inorder(tbt_node *);

// Driver code
int main(){
    tbt_node *root = NULL;
    int choice, data;

    // Initialize the tree with data
    init(&root);

    while (true) {
        printf("\n\t1. Insert\n\t2. Delete\n\t3. Inorder\n\t4. Exit\n\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n\tEnter the data to be inserted: ");
                scanf("%d", &data);
                insert(&root, data);
                break;
            case 2:
                printf("\n\tEnter the data to be deleted: ");
                scanf("%d", &data);
                delete(&root, data);
                break;
            case 3:
                printf("\n\tThe inorder traversal of the tree is\n");
                inorder(root);
                break;
            case 4:
                exit(0);
            default:
                printf("\n\tInvalid choice\n");
        }
    }
    return 0;
}

void init(tbt_node **root) {
    *root = NULL;
    int size;
    printf("\n\tEnter the number of elements to be inserted: ");
    scanf("%d", &size);
    system("clear");
    int* data = (int*)calloc(size, sizeof(int));
    printf("\n\tInitialize the tree with data: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &data[i]);
        insert(root, data[i]);
    }
    system("clear");
    // For displaying the tree
    printf("\n\tTree: ");
    inorder(*root);
    free(data); data = NULL;
}

void insert(tbt_node **root, int data) {
    tbt_node *p = NULL, *z = NULL, *head = *root;

    // Create a new node and initialize it
    z = (tbt_node *)calloc(1, sizeof(tbt_node));
    z->data = data;
    z->ltag = thread;
    z->rtag = thread;

    // If the tree is empty
    if (*root == NULL) {
        head = (tbt_node *)calloc(1, sizeof(tbt_node));

        // Treat entire tree as left subtree
        head->ltag = link;   head->rtag = thread;
        head->left_child = z;   head->right_child = head;
        head->data = -9999; // No data in head node

        *root = head;
        z->left_child = head;
        z->right_child = head;
    }
    else{ // If tree is not empty
        p = head->left_child;

        // Traverse for head node
        while (p != head) {
            if (p->data > data) {
                if (p->ltag != thread)  p = p->left_child;
                else{
                    z->left_child = p->left_child;
                    p->left_child = z;
                    p->ltag = link;
                    z->right_child = p;
                    z->rtag = thread;
                    return;
                }
            }
            else if (p->data < data) {
                if (p->rtag != thread)  p = p->right_child;
                else{
                    z->right_child = p->right_child;
                    p->right_child = z;
                    p->rtag = link;
                    z->left_child = p;
                    z->ltag = thread;
                    return;
                
                }
            }
            else {
                printf("\n\tThe data is already present in the tree\n");
                return;
            }
        }
    }
}

void delete(tbt_node **root, int data){
    tbt_node *head = (*root)->left_child; // head node
    tbt_node *parent = head;
    tbt_node *current = head->left_child; // current node
    tbt_node *pred = NULL;

    // Search for the node to delete and its parent
    while (current != head) {
        if (current->data == data)  break;
        parent = current;
        if (current->data > data) {
            if (current->ltag == thread)    return;
            current = current->left_child;
        }
        else{
            if (current->rtag == thread)    return;
            current = current->right_child;
        }
    }

    // If the node is not found
    if (current == head) {
        printf("\n\tThe data to be deleted is not found in the tree\n");
        return;
    }

    // Case 1: Node has both the children
    else if (current->ltag == link && current->rtag == link) {
        parent = current;
        pred = current->left_child;
        while (pred->rtag == link) {
            parent = pred;
            pred = pred->right_child;
        }
        current->data = pred->data;
        current = pred;
    }

    // Case 2: Node has one child
    else if (current->ltag == thread && current->rtag == link) {
        if (parent->left_child == current) { // has right child
            parent->left_child = current->right_child;
        } else {
            parent->right_child = current->right_child;
        }
        free(current); current = NULL;
        return;
    } else if (current->ltag == link && current->rtag == thread) { // has left child
        if (parent->left_child == current) {
            parent->left_child = current->left_child;
        } else {
            parent->right_child = current->left_child;
        }
        free(current); current = NULL;
        return;
    }

    // Case 3: Node has no child
    if (current->ltag == thread && current->rtag == thread) { 
        if (parent->left_child == current) {
            parent->ltag = thread;
            parent->left_child = current->left_child;
        } else {
            parent->rtag = thread;
            parent->right_child = current->right_child;
        }
        free(current); current = NULL;
        return;
    }
}