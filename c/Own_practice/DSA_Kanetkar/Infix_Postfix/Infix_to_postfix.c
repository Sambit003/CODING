//TODO: CHECK THE PROGRAM AGAIN AND CORRECT THE ERROR IN DISPLAYING THE POSTFIX EXPRESSION

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX 50

struct infix{
    char target[MAX];
    char stack[MAX];
    int top;
    char *s, *t;
};

//FUNCTION DECLARATIONS
void InitInfix(struct infix *); //Initializes the stack and top pointer
void SetExpression(struct infix *, char *); //Sets the expression to be evaluated
void Push(struct infix *, char); //Pushes an element onto the stack
char Pop(struct infix *); //Pops an element from the stack
void Convert(struct infix *); //Converts the infix expression to postfix expression
int Priority(char); //Returns the priority of the operator
void Display(struct infix); //Displays the postfix expression

//MAIN FUNCTION
int main(){
    struct infix p;
    char expr[MAX];
    
    InitInfix(&p);
    printf("\n\tEnter the infix expression: ");
    gets(expr); //Reads the expression from the user

    SetExpression(&p, expr); //Sets the expression to be evaluated
    Convert(&p); //Converts the infix expression to postfix expression

    printf("\n\tThe postfix expression is: "); //Displays the postfix expression
    Display(p);

    return 0;
}

//FUNCTION DEFINITIONS
/*Initializes structure elements*/
void InitInfix(struct infix *p){
    p->top = -1;
    strcpy(p->target, ""); //Initializes the target string to null
    strcpy(p->stack, ""); //Initializes the stack to null
    p->t=p->target; //Sets the target pointer to the beginning of the target string
    p->s=""; //Sets the source pointer to null 
}

/*Sets the expression to be evaluated*/
void SetExpression(struct infix *p, char *expr){
    p->s = expr; //Sets the source pointer to the beginning of the expression
}

/*Pushes an operator onto the stack*/
void Push(struct infix *p, char op){
    if(p->top == MAX-1){
        printf("\n\tStack Overflow");
        exit(1);
    }
    p->top++;
    p->stack[p->top] = op;
}

/*Pops an operator from the stack*/
char Pop(struct infix *p){
    if(p->top == -1){
        printf("\n\tStack Underflow");
        exit(1);
    }
    char op = p->stack[p->top];
    p->top--;
    return op;
}

/*Converts the infix expression to postfix expression*/
void Convert(struct infix *p){
    char opr;

    while(*(p->s)){
        if(*(p->s)==' '||*(p->s)=='\t'){
            p->s++;
            continue;
        }
        if(isdigit(*(p->s))||isalpha(*(p->s))){
            while(isdigit(*(p->s))||isalpha(*(p->s))){
                *(p->t)=*(p->s);
                p->s++;
                p->t++;
            }
        }
        if(*(p->s)=='('){
            Push(p,*(p->s));
            p->s++;
        }

        if(*(p->s)=='*'||*(p->s)=='+'||*(p->s)=='/'||*(p->s)=='%'||*(p->s)=='-'||*(p->s)=='$'){
            if(p->top==-1){
                Push(p,*(p->s));
            }
            else{
                opr = Pop(p);
                while(Priority(opr)>=Priority(*(p->s))){
                    *(p->t)=opr;
                    p->t++;
                    opr = Pop(p);
                }
                Push(p,opr);
                Push(p,*(p->s));
            }
            p->s++;
        }

        if(*(p->s)==')'){
            while((opr=Pop(p))!='('){
                *(p->t)=opr;
                p->t++;
            }
            p->s++;
        }
    }
    while(p->top!=-1){
        char opr = Pop(p);
        *(p->t)=opr;
        p->t++;
    }

    *(p->t)='\0'; //Appends null character to the end of the target string
}

/*Returns the priority of the operator*/
int Priority(char op){
    if(op == '(')
        return 0;
    else if(op == '+' || op == '-')
        return 1;
    else if(op == '*' || op == '/')
        return 2;
    else if(op == '$')
        return 3;
}

/*Displays the postfix expression*/
void Display(struct infix p){
    printf("%s", p.target);
}