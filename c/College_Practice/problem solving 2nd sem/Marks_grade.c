#include<stdio.h>
int main()
{
    int marks=0;
    printf("\n\tEnter marks : ");
    scanf("%d",&marks);
    if(marks<=100 && marks>=0)
    {
        printf("\n\tGrade : ");
        if(marks>=90)
            printf("A");
        else if(marks>=80 && marks<90)
            printf("B");
        else if(marks>=70 && marks<80)
            printf("C");
        else if(marks>=60 && marks<70)
            printf("D");
        else if(marks>=50 && marks<60)
            printf("E");
        else
            printf("F");
    }
    else
        printf("\n\tMarks can't exceed 100 or can't be lower than 0");
    return 0;
}