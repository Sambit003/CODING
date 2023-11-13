/*
    Intro to Heap:
    Heap is a special tree-based data structure in which the tree is a complete
    binary tree. Generally, Heaps can be of two types:

    1. Max-Heap: In a Max-Heap the key present at the root node must be greatest
    among the keys present at all of it’s children. The same property must be
    true recursively for all sub-trees in that Binary Tree.

    2. Min-Heap: In a Min-Heap the key present at the root node must be minimum
    among the keys present at all of it’s children. The same property must be
    true recursively for all sub-trees in that Binary Tree.

    Heap is a complete binary tree. A complete binary tree is a binary tree in
    which every level, except possibly the last, is completely filled, and all
    nodes are as far left as possible.

    Heap is a partially ordered data structure. The value of parent node is
    either greater than or equal to the value of child node in case of max heap.
    Similarly, value of parent node is either less than or equal to the value of
    child node in case of min heap.

    Formula for finding the index of the parent node of a node at index i:
        parent = (i - 1) / 2

    Formula for finding the index of the left child node of a node at index i:
        left_child = (2 * i) + 1

    Formula for finding the index of the right child node of a node at index i:
        right_child = (2 * i) + 2

    Heap is used in the implementation of priority queues.
*/

//CAUTION: This program is the mix of both heap and binary search tree.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node *left_child, *right_child;
} node;

int size = 0;

// This block is for function prototyping
void init(node **);
void insert(node **, int);
void delete(node **, int);
void heapify(node **, int, bool);
void de_heapify(node **, int, bool);
void do_min(node **, node **);
void do_max(node **, node **);
bool max_or_min(node *);
void preorder(node *);
int ascending_order(const void *, const void *);
int descending_order(const void *, const void *);
void store_values(node *, int [], int *);
void rebuild_tree(node **, int [], int, int);
void free_memory(node *);
void free_array(int []);

// Driver code
int main() {
    node *root = NULL;
    int choice, data;

    // Initialize the tree with data
    init(&root);
    printf("\n\tInitialized\n\n\tPress any key to continue...");
    getchar();

    while (true) {
        system("clear");
        printf("\n\t1. Insert\n\t2. Delete\n\t3. Display Heap\n\t4. Display Tree\n\t5. Reset Heap\n\t6. Exit\n\tEnter your choice: ");
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
                int displayChoice;
                while (true) {
                    printf("\n\t1. Min Heap\n\t2. Max Heap\n\tEnter your choice: ");
                    scanf("%d", &displayChoice);
                    switch (displayChoice) {
                        case 1:
                            heapify(&root, size, 0);
                            break;
                        case 2:
                            heapify(&root, size, 1);
                            break;
                        default:
                            printf("\n\tInvalid choice\n");
                            continue;
                    }
                }
                printf("\n\tThe Heap is: ");
                preorder(root);
                break;
            case 4:
                printf("\n\tThe tree is: ");
                preorder(root);
                break;
            case 5:
                if (max_or_min(root)) {
                    de_heapify(&root, size, 0);
                } else {
                    de_heapify(&root, size, 1);
                }
                printf("\n\tReset done\n\n\tPress any key to continue...");
                getchar();
                continue;
            case 6:
                exit(0);
            default:
                printf("\n\tInvalid choice\n");
                continue;
        }
    }

    return 0;
}

// Heap functions
void init(node **root) {
    *root = NULL;
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

void delete(node **root, int data) {
    if (*root == NULL) {
        printf("\n\tThe tree is empty\n");
    } else if (data < (*root)->data) {
        delete(&(*root)->left_child, data);
    } else if (data > (*root)->data) {
        delete(&(*root)->right_child, data);
    } else {
        node *temp = *root;
        if ((*root)->left_child == NULL) {
            *root = (*root)->right_child;
        } else if ((*root)->right_child == NULL) {
            *root = (*root)->left_child;
        } else {
            do_min(&temp, &(*root)->right_child);
            (*root)->data = temp->data;
            delete(&(*root)->right_child, (*root)->data);
        }
        free_memory(temp);
    }
}

void heapify(node **root, int size, bool trigger_max) {
    if (*root == NULL) {
        return; // Base case: Empty tree
    }

    node *current = *root;
    node *left_child = current->left_child;
    node *right_child = current->right_child;
    node *extreme = current; // Initialize with the current node as the extreme (min or max)

    if (trigger_max) {
        // For a max heap, find the maximum value among the current node and its children
        if (left_child != NULL && left_child->data > extreme->data) {
            extreme = left_child;
        }
        if (right_child != NULL && right_child->data > extreme->data) {
            extreme = right_child;
        }
    } else {
        // For a min heap, find the minimum value among the current node and its children
        if (left_child != NULL && left_child->data < extreme->data) {
            extreme = left_child;
        }
        if (right_child != NULL && right_child->data < extreme->data) {
            extreme = right_child;
        }
    }

    if (extreme != current) {
        // If the extreme value is not at the current node, swap them
        if (trigger_max) {
            do_max(&current, &extreme);
        } else {
            do_min(&current, &extreme);
        }

        // Recursively heapify the affected subtree
        heapify(&extreme, size, trigger_max);
    }

    // free the dynamically allocated memory
    free_memory(current);
    free_memory(left_child);
    free_memory(right_child);
    free_memory(extreme);
}

void de_heapify(node **root, int size, bool trigger_max) {
    // Reset the heap to a binary search tree
    // Create an array to store the values from the tree
    int *values = (int *)calloc(size, sizeof(int));

    // Traverse the tree and store its values in the array using in-order traversal
    int index = 0;
    store_values(*root, values, &index);

    // Sort the array in ascending or descending order, depending on whether it's max or min heap
    if (trigger_max) {
        // Sort the array in descending order (max heap)
        qsort(values, size, sizeof(int), descending_order);
    } else {
        // Sort the array in ascending order (min heap)
        qsort(values, size, sizeof(int), ascending_order);
    }

    // Rebuild the tree from the sorted array
    rebuild_tree(root, values, 0, size - 1);

    // Free the dynamically allocated memory for the array
    free_memory(values);

}

// Helper function to compare integers in ascending order (for qsort)
int ascending_order(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Helper function to compare integers in descending order (for qsort)
int descending_order(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

// Helper function to store the values of the tree in an array using in-order traversal
void store_values(node *root, int values[], int *index) {
    if (root == NULL) {
        return;
    }
    store_values(root->left_child, values, index);
    values[(*index)++] = root->data;
    store_values(root->right_child, values, index);
}

// Helper function to rebuild the tree from a sorted array
void rebuild_tree(node **root, int values[], int start, int end) {
    if (start > end) {
        return;
    }
    int mid = (start + end) / 2;
    node *newNode = (node *)calloc(1, sizeof(node));
    newNode->data = values[mid];
    newNode->left_child = NULL;
    newNode->right_child = NULL;
    rebuild_tree(&newNode->left_child, values, start, mid - 1);
    rebuild_tree(&newNode->right_child, values, mid + 1, end);
    *root = newNode;
}

void do_min(node **a, node **b) {
    // Min heap logic
    if ((*a)->data > (*b)->data) {
        int temp = (*a)->data;
        (*a)->data = (*b)->data;
        (*b)->data = temp;
    }
}

void do_max(node **a, node **b) {
    // Max heap logic
    if ((*a)->data < (*b)->data) {
        int temp = (*a)->data;
        (*a)->data = (*b)->data;
        (*b)->data = temp;
    }
}

bool max_or_min(node *root) {
    if (root == NULL) {
        return true; // An empty tree is considered a valid heap
    }

    int currentData = root->data;
    node *leftChild = root->left_child;
    node *rightChild = root->right_child;

    if (leftChild != NULL) {
        // Check the heap property with the left child
        if (currentData < leftChild->data) {
            return false;
        }
        if (!max_or_min(leftChild)) {
            return false;
        }
    }

    if (rightChild != NULL) {
        // Check the heap property with the right child
        if (currentData < rightChild->data) {
            return false;
        }
        if (!max_or_min(rightChild)) {
            return false;
        }
    }

    return true; // The tree is a valid heap
}

void preorder(node *root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left_child);
    preorder(root->right_child);
}

void free_memory(node *root) {
    if (root == NULL) return;
    free_memory(root->left_child);
    free_memory(root->right_child);
    free(root); root = NULL;
}

void free_array(int *arr) {
    if (arr == NULL) return;
    free(arr); arr = NULL;
}