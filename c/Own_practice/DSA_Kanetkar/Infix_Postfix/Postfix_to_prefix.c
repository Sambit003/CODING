//TODO: FINISH THIS PROGRAM, PAGE : 140, KANETKAR, DATA STRUCTURES THROUGH C

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 50

struct postfix{
    char target[MAX], stack[MAX]; //target string and stack
    int i,top; //top pointer and index variable for target string
    char temp1[2], temp2[2]; //Temporary strings to hold the operands
    char str1[MAX], str2[MAX], str3[MAX]; //Temporary strings to hold the operands
};

//FUNCTION DECLARATIONS
void InitPostfix(struct postfix *); //Initializes the stack and top pointer
void SetExpression(struct postfix *, char *); //Sets the expression to be evaluated
void Push(struct postfix *, char *); //Pushes an element onto the stack
void Pop(struct postfix *,char *); //Pops an element from the stack
void Convert(struct postfix *); //Converts the postfix expression to prefix expression
void Display(struct postfix); //Displays the prefix expression

//MAIN FUNCTION
int main(){
    struct postfix q;
    char expr[MAX];

    InitPostfix(&q); //Initializes the stack and top pointer
    printf("\n\tEnter the postfix expression: "); //Reads the expression from the user
    gets(expr);
    SetExpression(&q, expr); //Sets the expression to be evaluated

    Convert(&q); //Converts the postfix expression to prefix expression
    printf("\n\tThe prefix expression is: "); //Displays the prefix expression
    Display(q);

    return 0;
}

//FUNCTION DEFINITIONS
/*Initializes structure elements*/
void InitPostfix(struct postfix *q){
    q->top = -1;
    q->i=0; //Sets the index variable to 0
    strcpy(q->target,""); //Initializes the target string to null
}

/*Copies the given expression to target string*/
void SetExpression(struct postfix *q, char *expr){
    strcpy(q->target, expr); //Copies the given expression to target string
}

/*Pushes an operator onto the stack*/
void Push(struct postfix *q, char *op){
    if(q->top == MAX-1){
        printf("\n\tStack Overflow");
        return;
    }
    q->top++;
    strcpy(q->stack[q->top], op); //Pushes the operator onto the stack
}

/*Pops an operator from the stack*/
void Pop(struct postfix *q, char *op){
    if(q->top == -1){
        printf("\n\tStack Underflow");
        return;
    }
    strcpy(op, q->stack[q->top]); //Pops the operator from the stack
    q->top--;
}

/*Converts the postfix expression to prefix expression*/
void Convert(struct postfix *q){
    while(q->target[q->i] != '\0'){
        /*skip whitespace, if any*/
        if(q->target[q->i]==' ')
            q->i++;
        else if(q->target[q->i]=='%' || q->target[q->i]=='*' || q->target[q->i]=='-' || q->target[q->i]=='+' || q->target[q->i]=='/' || q->target[q->i]=='$'){
            Pop(q,q->str2);
            Pop(q,q->str3);
            q->temp1[0]=q->target[q->i];
            q->temp1[1]='\0';
            strcpy(q->str1,q->temp1);
            strcat(q->str1,q->str3);
            strcat(q->str1,q->str2);
            Push(q,q->str1);
        }
        else{
            q->temp1[0]=q->target[q->i];
            q->temp1[1]='\0';
            strcpy(q->temp2,q->temp1);
            Push(q,q->temp2);
        }
        q->i++;
    }
}

/*Displays the prefix expression*/
void Display(struct postfix q){
    char *temp=q.stack[0];
    while(*temp){
        printf("%c",*temp);
        temp++;
    }
}