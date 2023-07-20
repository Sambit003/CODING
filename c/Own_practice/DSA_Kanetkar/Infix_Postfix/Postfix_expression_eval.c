#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#define MAX 50

struct postfix{
    int stack[MAX];
    int top, nn;
    char *s;
};

//FUNCTION DECLARATIONS
void InitPostfix(struct postfix *); //Initializes the stack and top pointer
void SetExpression(struct postfix *, char *); //Sets the expression to be evaluated
void Push(struct postfix *, int); //Pushes an element onto the stack
int Pop(struct postfix *); //Pops an element from the stack
void Evaluate(struct postfix *); //Evaluates the postfix expression
void Display(struct postfix); //Displays the result

//MAIN FUNCTION
int main(){
    struct postfix p;
    char expr[MAX];
    
    InitPostfix(&p);
    printf("\n\tEnter the postfix expression: ");
    gets(expr); //Reads the expression from the user
    SetExpression(&p, expr); //Sets the expression to be evaluated
    
    Evaluate(&p); //Evaluates the postfix expression
    printf("\n\tThe result is: "); //Displays the result
    Display(p);

    return 0;
}

//FUNCTION DEFINITIONS
/*Initializes structure elements*/
void InitPostfix(struct postfix *p){
    p->top = -1;
    p->s=""; //Sets the source pointer to null 
}

/*Sets the expression to be evaluated*/
void SetExpression(struct postfix *p, char *expr){
    p->s = expr; //Sets the source pointer to the beginning of the expression
}

/*Pushes the digits on to stack*/
void Push(struct postfix *p, int nn){
    if(p->top == MAX-1){
        printf("\n\tStack Overflow");
        exit(1);
    }
    p->top++;
    p->stack[p->top] = nn;
}

/*Pops the digits from the stack*/
int Pop(struct postfix *p){
    if(p->top == -1){
        printf("\n\tStack Underflow");
        exit(1);
    }
    p->nn = p->stack[p->top];
    p->top--;
    return p->nn;
}

/*Evaluates the postfix expression*/
void Evaluate(struct postfix *p){
    int n1, n2, n3;
    while(*p->s != '\0'){
        if(isdigit(*p->s)){
            Push(p, *p->s - '0');
        }
        else{
            /*if operator is encoutered*/
            n1 = Pop(p);
            n2 = Pop(p);
            switch(*(p->s)){
                case '+':
                    n3 = n2 + n1;
                    break;
                case '-': 
                    n3 = n2 - n1;
                    break;
                case '*':
                    n3 = n2 * n1;
                    break;
                case '/':
                    n3 = n2 / n1;
                    break;
                case '%':
                    n3 = n2 % n1;
                    break;
                case '$':
                    n3 = (int)pow((double)n2, (double)n1);
                    break;
                default:
                    printf("\n\tInvalid operator");
                    exit(1);
            }
            Push(p, n3);
        }
        p->s++;
    }
}

/*Displays the result*/
void Display(struct postfix p){
    p.nn = Pop(&p);
    printf("Result is: %d\n", p.nn);
}
