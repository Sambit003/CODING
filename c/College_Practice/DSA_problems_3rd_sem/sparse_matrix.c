/*
    What is Sparse matrix?
    ans: A sparse matrix is a matrix in which most of its elements are zero. 
    In contrast to a dense matrix, where most elements have non-zero values, 
    a sparse matrix contains very few non-zero elements relative to its total size. 
    Sparse matrices are common in various computational and scientific applications 
    where memory efficiency and computational speed are important.

    Sparse matrices are used to represent and store data in situations where the
    majority of the information is zero, such as in finite element analysis, numerical simulations, 
    data mining, and graph algorithms. 
    Storing sparse matrices in their dense form would be highly inefficient in terms of 
    memory usage, so specialized data structures and algorithms
    are employed to handle sparse matrices more efficiently.
*/

// This program is based on array concept
#include<stdio.h>
#include<stdlib.h>

const int MAX1 = 3, MAX2 = 3;

typedef struct sparse {
    int *sp;
    int row;
} sparse;

// This block is for function prototyping
// Block 0: For common functions
void init_sparse(sparse *);
void delete_sparse(sparse *);
int count(sparse);
void transpose(sparse *, sparse);
// Block 1: For array representation
void create_array(sparse *); // Why array?? - Because we are using array to store the sparse matrix
void display_array(sparse);
// Block 2: For tuple representation
void create_tuple(sparse *, sparse); // Why tuple?? - Common way of representing the sparse matrix is 3-tuple form
void display_tuple(sparse);


// Driver code
int main() {
    sparse s1, s2;
    int choice;

    init_sparse(&s1);
    init_sparse(&s2);

    printf("\n\tEnter the elements of the matrix\n");
    create_array(&s1);
    display_array(s1);

    int c = count(s1);
    printf("\n\tThe number of non-zero elements in the matrix is %d\n", c);

    create_tuple(&s2, s1);
    printf("\n\tThe tuple representation of the matrix is\n");
    display_tuple(s2);

    transpose(&s1, s2);
    printf("\n\tThe transpose of the matrix is\n");
    display_tuple(s1);

    delete_sparse(&s1);
    delete_sparse(&s2);

    return 0;
}

// This block is for defining the functions
// Block 0: For common functions
void init_sparse(sparse *s) {
    s->sp = NULL;
}

void delete_sparse(sparse *s) {
    free(s->sp);
    s->sp = NULL;
}

int count(sparse s) {
    int count = 0;
    for(int i = 0; i < MAX1*MAX2; i++) {
        if(*(s.sp + i) != 0) {
            count++;
        }
    }
    return count;
}

void transpose(sparse *s1, sparse s2){
    int x, q, position_1, position_2, column, element, c, y;

    s1->sp = (int*)calloc(s2.row*3, sizeof(int));
    s1->row = s2.row;

    //store the informations
    *(s1->sp + 0) = *(s2.sp + 1);
    *(s1->sp + 1) = *(s2.sp + 0);
    *(s1->sp + 2) = *(s2.sp + 2);

    column = *(s2.sp + 1);
    element = *(s2.sp + 2);

    if(element <= 0)    return;

    x = 1; // x is used to keep track of 
    for(c = 0; c < column; c++) {
        for(y = 1; y <= element; y++) {
            q = y*3+1; 
            if(*(s2.sp + q) == c) {
                position_2 = x*3+0;     position_1 = x*3+1;
                *(s1->sp + position_2) = *(s2.sp + position_1);

                position_2 = x*3+1;     position_1 = x*3+0;
                *(s1->sp + position_2) = *(s2.sp + position_1);

                position_2 = x*3+2;     position_1 = x*3+2;
                *(s1->sp + position_2) = *(s2.sp + position_1);

                x++;
            }
        }
    }
}

// Block 1: For array representation
void create_array(sparse *s){
    SET_SIZE: s->sp = (int*)calloc(MAX1*MAX2, sizeof(int));
    
    if(s->sp == NULL) {
        printf("\n\tMemory allocation failed\n");
        goto SET_SIZE;
    }
    else{
        printf("\n\tEnter the elements of the matrix\n");
        for(int i = 0; i < MAX1*MAX2; i++) {
            scanf("%d", s->sp + i);
        }
        printf("\n");
    }
}

void display_array(sparse s) {
    printf("\n\tThe matrix is\n");
    for(int i = 0; i < MAX1*MAX2; i++) {
        printf("%d ", *(s.sp + i));
        if((i+1)%MAX2 == 0) {
            printf("\n");
        }
    }
    printf("\n\n");
}

// Block 2: For tuple representation
void create_tuple(sparse *s1, sparse s2){
    int row=0, col=-1, len=-1;

    s1->row = count(s2)+1;

    s1->sp = (int*)calloc(s1->row*3, sizeof(int));
    *(s1->sp + 0) = MAX1;
    *(s1->sp + 1) = MAX2;
    *(s1->sp + 2) = s1->row-1;

    len = 2; // len is used to keep track of the index of the sparse matrix
    for(int i = 0; i < MAX1*MAX2; i++) {
        col++;
        if(((i%MAX2)==0)&&(i!=0)) {
            row++;
            col = 0;
        }
        if(*(s2.sp + i) != 0) {
            *(s1->sp + ++len) = i/MAX2;
            *(s1->sp + ++len) = i%MAX2;
            *(s1->sp + ++len) = *(s2.sp + i);
        }
    }
}

void display_tuple(sparse s) {
    printf("\n\tThe matrix is\n");
    for(int i = 0; i < s.row*3; i++) {
        printf("%d ", *(s.sp + i));
        if((i+1)%3 == 0) {
            printf("\n");
        }
    }
    printf("\n\n");
}