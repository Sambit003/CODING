#include<stdio.h>
#include<stdlib.h>
#define MAX1 3
#define MAX2 3
#define MAXSIZE 9
#define BIGNUM 100

typedef struct sparse{
    int *sp, *result, row;
}SparseMatrix;

/*Initialises element of the structure */
void InitSparse(SparseMatrix *ptr){
    ptr->sp=NULL;   ptr->result=NULL;
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

/*Carries out addition of two matrices*/
void AddMatrix(SparseMatrix *ptr, SparseMatrix s1, SparseMatrix s2){
    int i=1, j=1, k=1, element=1, max, maxA, maxB, rowA, rowB, colA, colB, valueA, valueB;

    /*Get the total number of non-zeero values from both matrices*/
    maxA=*(s1.sp+2);
    maxB=*(s2.sp+2);
    max=maxA+maxB;
    /*Allocate memory for result*/
    ptr->result=(int *)malloc(MAXSIZE*3* sizeof(int));

    while(element<=max){
        /*Check if i<max. Non-zero values in first 3-tuple and get the values*/
        if(i<=maxA){
            rowA=*(s1.sp+i*3+0);
            rowB=*(s1.sp+i*3+1);
            valueA=*(s1.sp+i*3+2);
        }
        else    rowA=colA=BIGNUM;

        /*Chec if j<max. Non-zero values in second 3-tuple and get the values*/
        if(j<=maxB){
            rowB=*(s2.sp+j*3+0);
            colB=*(s2.sp+j*3+1);
            valueB=*(s2.sp+j*3+2);
        }
        else    rowB=colB=BIGNUM;

        /*If row no. of both 3-tuple are same*/
        if(rowA==rowB){
            /*If col no. of both 3-tuple are same*/
            if (colA==colB){
                /*Add two non-zero values store in result*/
                *(ptr->result+k*3+0)=rowA;
                *(ptr->result+k*3+1)=rowA;
                *(ptr->result+k*3+2)=valueA+valueB;
                i++;    j++;    max--;
            }
            
            /*If col. number of first 3-tuple is <col no. of second 3-tuple, then add info as it is to the result*/
            if(colA<colB){
                *(ptr->result+k*3+0)=rowA;
                *(ptr->result+k*3+1)=rowA;
                *(ptr->result+k*3+2)=valueA;
                i++;
            }

            /*If col number of first 3-tuple is >col. number of second tuple, then add info. as it is to the result*/
            if(colA>colB){
                *(ptr->result+k*3+0)=rowB;
                *(ptr->result+k*3+1)=rowB;
                *(ptr->result+k*3+2)=valueB;
                j++;
            }
            k++;
        }

        /*If row number of first 3-tuple is <row number of second 3-tuple, then add info as it is to the result*/
        if(rowA<rowB){
            *(ptr->result+k*3+0)=rowA;
            *(ptr->result+k*3+1)=colA;
            *(ptr->result+k*3+2)=valueA;
            i++;    k++;
        }

        /*If row number of first 3-tuple is >row number of second 3-tuple, then add info as it is to the result*/
        if (rowA>rowB){
            *(ptr->result+k*3+0)=rowB;
            *(ptr->result+k*3+1)=colB;
            *(ptr->result+k*3+2)=valueB;
            j++;    k++;
        }
        element++;   
    }

    /*Add info about the total number of rows,columns and non-zero alues that the resultant array contains to the result*/
    *(ptr->result+0)=MAX1;
    *(ptr->result+1)=MAX2;
    *(ptr->result+2)=max;
}

/*Displays the contents of the matrix*/
void DisplayResult(SparseMatrix s){
    
    /*The loop traverses the entire matrix*/
    for(int i=0; i<(*(s.result+0+2)+1)*3; i++){
        if(i%3==0)  printf("\n");   //Positions the cursor to the new line for every new row
        printf("%d\t",*(s.result+i));
    }
    printf("\n\n");
}

/*Dealocates the memory*/
void DeleteSparse(SparseMatrix *ptr){
    if(ptr->sp!=NULL)   free(ptr->sp);
    if(ptr->result!=NULL) free(ptr->result);
}

int main(){
    SparseMatrix s[5];

    for(int i=0; i<5; i++)  InitSparse(&s[i]);

    CreateArray(&s[0]);

    CreateTuple(&s[1], s[0]);
    DisplayTuples(s[1]);

    CreateArray(&s[2]);

    CreateTuple(&s[3], s[2]);
    DisplayTuples(s[3]); 

    AddMatrix(&s[4],s[1],s[3]);

    printf("\n\tResult of addition of two matrices: ");
    DisplayResult(s[4]);

    for(int i=0; i<5; i++)  DeleteSparse(&s[i]);

    return 0;
}