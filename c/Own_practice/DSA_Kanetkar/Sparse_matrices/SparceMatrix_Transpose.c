#include<stdio.h>
#include<stdlib.h>
#define MAX1 3
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
        if(((1%MAX2)==0)&&(i!=0)){
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

/*Obtains transpose of an array*/
void Transpose(SparseMatrix *ptr, SparseMatrix s){
    int q, Pos1, Pos2, col, element;

    /*Allocates the memory*/
    ptr->sp = (int *) malloc(s.row*3* sizeof(int));
    ptr->row=s.row;

    /*Store total number of rows, cols and non zero elements*/
    *(ptr->sp+0)=*(s.sp+1);
    *(ptr->sp+1)=*(s.sp+0);
    *(ptr->sp+2)=*(s.sp+2);

    col=*(ptr->sp+1);
    element=*(ptr->sp+2);

    if(element<=0)  return;

    int x=1;

    for(int c=0; c<col; c++){
        for(int y=1; y<=element; y++){
            q=y*3+1;
            if(*(s.sp+q)==c){
                Pos2=x*3+0;
                Pos1=y*3+1;
                *(ptr->sp+Pos2)=*(s.sp+Pos1);

                Pos2=x*3+1;
                Pos1=y*3+0;
                *(ptr->sp+Pos2)=*(s.sp+Pos1);

                Pos2=x*3+2;
                Pos1=y*3+2;
                *(ptr->sp+Pos2)=*(s.sp+Pos1);

                x++;
            }
        }
    }
}

/*Displays the 3-tuple form after transpose operation*/
void DisplayTransposes(SparseMatrix ptr){
    for(int i=0; i<ptr.row*3; i++){
        if(i%3==0)  printf("\n");
        printf("%d\t",*(ptr.sp+i));
    }
}

/*Dealocates the memory*/
void DeleteSparse(SparseMatrix *ptr){
    free(ptr->sp);
}

int main(){
    SparseMatrix s[3];  int c;

    for(int i=0; i<3; i++){
        InitSparse(&s[i]);
    }

    CreateArray(&s[0]);

    printf("\n\tElements in Sparse Matrix: ");
    Display(s[0]);

    c=Count(s[0]);
    printf("\n\tNumber of non zero elements in Sparse Matrix: %d\n\n",c);

    CreateTuple(&s[1], s[0]);
    printf("\n\tArray of non zero elements: ");
    DisplayTuples(s[1]);

    Transpose(&s[2],s[1]);
    printf("\n\tTransposed: ");
    DisplayTransposes(s[2]);

    for(int j=0;j<3;j++){
        DeleteSparse(&s[j]);
    }  

    return 0;
}