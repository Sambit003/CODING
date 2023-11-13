/*
    Binary Search Tree implementation. You must have the knowledge of
    Linked List, Recursion, Pointers, Dynamic Memory Allocation, etc.
    to understand this code.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node *left_child, *right_child;
} node;

// This block is for function prototyping
void init(node **);
void insert(node **, int);
void delete(node **, int);
void inorder(node *);
void preorder(node *);
int search(node *, int);
void locate_node(node **, int, node **, node **, int *);

// Driver code
int main(){
    node *root = NULL;
    int choice, data, found;

    // Initialize the tree with data
    init(&root);

    while (true) {
        printf("\n\t1. Insert\n\t2. Delete\n\t3. Inorder\n\t4. Preorder\n\t5. Search\n\t6. Exit\n\tEnter your choice: ");
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
                printf("\n\tThe preorder traversal of the tree is\n");
                preorder(root);
                break;
            case 5:
                printf("\n\tEnter the data to be searched: ");
                scanf("%d", &data);
                found = search(root, data);
                if (found)
                    printf("\n\tThe data is found in the tree\n");
                else
                    printf("\n\tThe data is not found in the tree\n");
                break;
            case 6:
                exit(0);
            default:
                printf("\n\tInvalid choice\n");
        }
    }

    return 0;
}

// This block is for defining the functions
void init(node **root) {
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
    // For displaying the tree
    printf("\n\tTree: ");
    inorder(*root);
    free(data); data = NULL;
}

void insert(node **n, int data) {
    if (*n == NULL) {
        *n = (node *)malloc(sizeof(node));
        (*n)->data = data;
        (*n)->left_child = NULL;
        (*n)->right_child = NULL;
    } else if (data < (*n)->data) {
        insert(&(*n)->left_child, data);
    } else if (data > (*n)->data) {
        insert(&(*n)->right_child, data);
    } else {
        printf("\n\tThe data is already present in the tree\n");
    }
}

void delete(node **n, int data){
    int found;
    node *parent = NULL, *x = NULL, *xsucc = NULL; // x is the node to be deleted, xsucc is the successor of x
    if (*n == NULL) {
        printf("\n\tThe tree is empty\n");
        return;
    }

    locate_node(n, data, &parent, &x, &found);

    // Case 1: Node not found
    if (found == false){
        printf("\n\tThe data to be deleted is not found in the tree\n");
        return;
    }

    // Case 2: Node has both the children
    if (x->left_child != NULL && x->right_child != NULL) {
        parent = x;
        xsucc = x->right_child;
        while (xsucc->left_child != NULL) {
            parent = xsucc;
            xsucc = xsucc->left_child;
        }
        x->data = xsucc->data;
        x = xsucc;
    }

    // Case 3: Node has one child
    if (x->left_child == NULL && x->right_child != NULL) { // has right child
        if (parent->left_child == x) {
            parent->left_child = x->right_child;
        } else {
            parent->right_child = x->right_child;
        }
        free(x); x = NULL;
        return;
    } else if (x->left_child != NULL && x->right_child == NULL) { // has left child
        if (parent->left_child == x) {
            parent->left_child = x->left_child;
        } else {
            parent->right_child = x->left_child;
        }
        free(x); x = NULL;
        return;
    }

    // Case 4: Node has no child
    if (x->left_child == NULL && x->right_child == NULL) {
        if (parent->left_child == x) {
            parent->left_child = NULL;
        } else {
            parent->right_child = NULL;
        }
        free(x); x = NULL;
        return;
    }
}

void inorder(node *n) {
    if (n != NULL) {
        inorder(n->left_child);
        printf("%d ", n->data);
        inorder(n->right_child);
    }
}

void preorder(node *n) {
    if (n != NULL) {
        printf("%d ", n->data);
        preorder(n->left_child);
        preorder(n->right_child);
    }
}

void postorder(node *n) {
    if (n != NULL) {
        postorder(n->left_child);
        postorder(n->right_child);
        printf("%d ", n->data);
    }
}

int search(node *n, int data) {
    while (n != NULL) {
        if (data > n->data) {
            n = n->right_child;
        } else if (data < n->data) {
            n = n->left_child;
        } else {
            return 1;
        }
    }
    return 0;
}

void locate_node(node **root, int data, node **parent, node **x, int *found) {
    node *q = *root;
    *found = false;
    *parent = NULL;

    while (q != NULL) {
        if (q->data == data) {
            *found = true;
            *x = q;
            return;
        }
        *parent = q;
        if (q->data > data) {
            q = q->left_child;
        } else {
            q = q->right_child;
        }
    }
}