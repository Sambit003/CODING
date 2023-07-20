// Write a program to store the name of teachers and salary of an institute within a structure, then print the name of highest salary paid teacher.
#include <stdio.h>
#include <string.h>
struct teacher{
    char name[20];
    float salary;
};
int main(){
    struct teacher t[10];
    int i, n;
    float max;
    printf("Enter the number of teachers: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++){
        printf("Enter the name of teacher %d: ", i + 1);
        scanf("%s", t[i].name);
        printf("Enter the salary of teacher %d: ", i + 1);
        scanf("%f", &t[i].salary);
    }
    max = t[0].salary;
    for (i = 0; i < n; i++){
        if (t[i].salary > max)      max = t[i].salary;
    }
    for (i = 0; i < n; i++){
        if (t[i].salary == max)     printf("The name of highest salary paid teacher is %s", t[i].name);
    }
    return 0;
}