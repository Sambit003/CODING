/*
    Intro about AVL Tree:
    AVL tree is a self-balancing Binary Search Tree (BST) where the difference
    between heights of left and right subtrees cannot be more than one for all
    nodes.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node *left_child, *right_child;
    int height;
} node;

// Function prototypes for AVL tree operations
void init(node **);
int max(int, int);
node* insert(node *, int);
node* delete(node *, int);
node* left_rotate(node *);
node* right_rotate(node *);
node* min_value_node(node *);
void display_tree(node *);
int get_height(node *);
int get_balance_factor(node *);

int main() {
    node *root = NULL;
    int choice, data;

    init(&root);
    printf("\n\tInitialized\n\n\tPress any key to continue...");
    getchar();

    while (true) {
        system("clear");
        printf("\n\t1. Insert\n\t2. Delete\n\t3. Display Tree\n\t4. Exit\n\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n\tEnter the data to be inserted: ");
                scanf("%d", &data);
                root = insert(root, data);
                break;
            case 2:
                printf("\n\tEnter the data to be deleted: ");
                scanf("%d", &data);
                root = delete(root, data);
                break;
            case 3:
                printf("\n\tThe tree is: ");
                display_tree(root);
                break;
            case 4:
                exit(0);
            default:
                printf("\n\tInvalid choice\n");
        }
    }

    return 0;
}

// AVL tree functions
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
        *root = insert(*root, data[i]); // Dereference root here
    }
    // For displaying the tree
    printf("\n\tTree: ");
    display_tree(*root);
    free(data); data = NULL;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int get_height(node *n) {
    if (n == NULL)
        return 0;
    return n->height;
}

int get_balance_factor(node *n) {
    if (n == NULL)
        return 0;
    return get_height(n->left_child) - get_height(n->right_child);
}

node *right_rotate(node *y) {
    node *x = y->left_child;
    node *T2 = x->right_child;

    x->right_child = y;
    y->left_child = T2;

    y->height = max(get_height(y->left_child), get_height(y->right_child)) + 1;
    x->height = max(get_height(x->left_child), get_height(x->right_child)) + 1;

    return x;
}

node *left_rotate(node *x) {
    node *y = x->right_child;
    node *T2 = y->left_child;

    y->left_child = x;
    x->right_child = T2;

    x->height = max(get_height(x->left_child), get_height(x->right_child)) + 1;
    y->height = max(get_height(y->left_child), get_height(y->right_child)) + 1;

    return y;
}

node* insert(node* root, int data) {
    if (root == NULL) {
        node* newNode = (node*)malloc(sizeof(node));
        newNode->data = data;
        newNode->left_child = newNode->right_child = NULL;
        newNode->height = 1;
        return newNode;
    }

    if (data < root->data)
        root->left_child = insert(root->left_child, data);
    else if (data > root->data)
        root->right_child = insert(root->right_child, data);
    else
        return root; // Duplicate data is not allowed

    root->height = 1 + max(get_height(root->left_child), get_height(root->right_child));
    int balance = get_balance_factor(root);

    // Left Heavy
    if (balance > 1) {
        if (data < root->left_child->data) // Left-Left
            return right_rotate(root);
        if (data > root->left_child->data) { // Left-Right
            root->left_child = left_rotate(root->left_child);
            return right_rotate(root);
        }
    }

    // Right Heavy
    if (balance < -1) {
        if (data > root->right_child->data) // Right-Right
            return left_rotate(root);
        if (data < root->right_child->data) { // Right-Left
            root->right_child = right_rotate(root->right_child);
            return left_rotate(root);
        }
    }

    return root;
}

node* min_value_node(node* root) {
    node* current = root;
    while (current->left_child != NULL)
        current = current->left_child;
    return current;
}

node* delete(node* root, int data) {
    if (root == NULL)
        return root;

    if (data < root->data)
        root->left_child = delete(root->left_child, data);
    else if (data > root->data)
        root->right_child = delete(root->right_child, data);
    else {
        if ((root->left_child == NULL) || (root->right_child == NULL)) {
            node* temp = root->left_child ? root->left_child : root->right_child;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            node* temp = min_value_node(root->right_child);
            root->data = temp->data;
            root->right_child = delete(root->right_child, temp->data);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(get_height(root->left_child), get_height(root->right_child));
    int balance = get_balance_factor(root);

    // Left Heavy
    if (balance > 1) {
        if (get_balance_factor(root->left_child) >= 0) // Left-Left
            return right_rotate(root);
        if (get_balance_factor(root->left_child) < 0) { // Left-Right
            root->left_child = left_rotate(root->left_child);
            return right_rotate(root);
        }
    }

    // Right Heavy
    if (balance < -1) {
        if (get_balance_factor(root->right_child) <= 0) // Right-Right
            return left_rotate(root);
        if (get_balance_factor(root->right_child) > 0) { // Right-Left
            root->right_child = right_rotate(root->right_child);
            return left_rotate(root);
        }
    }

    return root;
}

void display_tree(node *root) {
    if (root != NULL) {
        display_tree(root->left_child);
        printf("%d ", root->data);
        display_tree(root->right_child);
    }
}
