#include<stdio.h>
#define size 5
int CheckSame(int* arr, int num)
{
    int count = 0;
    for (int i = 1; i <= (num - 1); i++)
    {
        if (arr[i] == arr[i - 1])
        {
            count++;
        }
    }
    if (count == (num - 1))
    {
        return (num-1);
    }
    return 0;
}
int main()
{
    int num,status;
    printf("UPTO:");
    scanf("%d",&num);
    int a[size];
    for (int i = 1; i <=num; i++)
    {
        printf("a[%d]:",i);
        scanf("%d",&a[i]);
        printf("\n");
    }
    status=CheckSame(a,num);
    if (status>0)
    {
        printf("%d",status);
    }   
    return 0;
}