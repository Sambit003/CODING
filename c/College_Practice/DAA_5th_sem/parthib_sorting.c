//PARTHIB'S CODE

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int check_sorted(int *arr, int n)
{
    for (int i = 0; i < n-1; i++)
    {
        if (*(arr + i) > *(arr + i+1))
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    int n, i, j, temp, arr[20];
    while (1)
    {
        printf("\n\t\tSIZE:");
        scanf("%d", &n);
        system("cls");
        if (n > 0 && n <= 20)
        {
            for (i = 0; i < n; i++)
            {
                printf("\n\t\tELEM[%d]:", i);
                scanf("%d", &arr[i]);
            }

            if (check_sorted(arr, n) == 1)
            {
                printf("\n\t\tARRAY ALREADY SORTED!!,PRESS ANY KEY TO CONTINUE:");
                getch();
                continue;
            }
            else
            {
                for (j = 0; j < n - 1; j++)
                {
                    for (i = 0; i < n - 1 - j; i++)
                    {
                        if (arr[i] > arr[i + 1])
                        {
                            temp = arr[i];
                            arr[i] = arr[i + 1];
                            arr[i + 1] = temp;
                        }
                    }
                }
            }

            printf("\n\t\tSORTED ARRAY:\t");
            for (i = 0; i < n; i++)
            {
                printf("%d\t", arr[i]);
            }
            printf("\n\t\tPRESS ANY KEY TO CONTINUE:");
            getch();
        }
        else
        {
            printf("\n\t\tINVALID SIZE!!");
            exit(0);
        }
    }
    return 0;
}