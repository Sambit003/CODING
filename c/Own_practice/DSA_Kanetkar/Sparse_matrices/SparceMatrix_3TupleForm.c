#include<stdio.h>
#include<stdlib.h>
#define MAX1 2
#define MAX2 3

typedef struct sparse{
    int *sp, row;
}SparseMatrix;

/*Initialises element of the structure */
void InitSparse(SparseMatrix *ptr){
    ptr->sp=NULL;
}

/*Dynamically creates the matrix of size MAX1 x MAX2*/
void CreateArray(SparseMatrix *ptr){
    int n;

    ptr->sp=(int *)malloc(MAX1 * MAX2 * sizeof(int));

    for(int i=0;i<MAX1*MAX2;i++){
        printf("\n\tEnter element no %d: ",i);
        scanf("%d",&n);
        *(ptr->sp+i)=n;
    }
}

/*Displays the contents of the matrix*/
void Display(SparseMatrix ptr){
    /*The loop will traverse the entire matrix*/
    for(int i=0;i<MAX1*MAX2;i++){
        if(i%MAX2==0)   printf("\n");  //Positions the cursor to the new line for every new row
        printf("\t%d",*(ptr.sp+i));
    }
}

/*Counts the number of non-zero elements*/
int Count(SparseMatrix ptr){
    int count=0;
    
    for(int i=0; i<MAX1*MAX2;i++)   if(*(ptr.sp+i)!=0)  count++;
    return count;
}

/*Creates an array which stores the information of non-zero elements*/
void CreateTuple(SparseMatrix *ptr, SparseMatrix s){
    int row=0, col=0, line=(-1);

    ptr->row=Count(s)+1;

    ptr->sp=(int *) malloc(ptr->row * 3 * sizeof(int));
    *(ptr->sp+0) = MAX1;
    *(ptr->sp+1) = MAX2;
    *(ptr->sp+2) = ptr->row-1;

    line=2;

    for(int i=0; i<MAX1*MAX2; i++){
        col++;

        /*Sets the row and column values*/
        if(((i%MAX2)==0)&&(i!=0)){
            row++;  col=0;
        }

        /*checks for non-zero elements row, column and non-zero element value is assigned to matrix*/
        if(*(s.sp+i)!=0){
            line++;
            *(ptr->sp+line)=row;
            line++;
            *(ptr->sp+line)=col;
            line++;
            *(ptr->sp+line)=*(s.sp+i);
        }
    }
}

/*Displays the contents of 3-tuple*/
void DisplayTuples(SparseMatrix ptr){
    for(int i=0;i<ptr.row*3;i++){
        if(i%3==0)   printf("\n");
        printf("%d\t",*(ptr.sp+i));
    }
}

/*Dealocates the memory*/
void DeleteSparse(SparseMatrix *ptr){
    free(ptr->sp);
}

int main(){
    SparseMatrix s1, s2;    int c;

    InitSparse(&s1);
    InitSparse(&s2);

    CreateArray(&s1);
    printf("\n\tElements in sparse matrix: ");
    Display(s1);

    c=Count(s1);
    printf("\n\n\tNumber of nonzeros in sparse matrix: %d",c);

    CreateTuple(&s2,s1);
    printf("\n\n\tArray of non-zero element: ");
    DisplayTuples(s2);

    DeleteSparse(&s1);
    DeleteSparse(&s2);

    return 0;
}