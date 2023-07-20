#include<stdio.h>
int main()
{
    int arr[20],i,j,n,temp;
    printf("\n\tEnter how many elements you want to insert: ");
    scanf("%d",&n);
    printf("\n\tEnter the elements: ");
    for(i=0;i<n;i++)
        scanf("%d",&arr[i]);
    for(i=0,j=n-1;i<j;i++,j--)
    {
        temp=arr[i];
        arr[i]=arr[j];
        arr[j]=temp;
    }
    printf("\n\tArray after reversing: ");
    for(i=0;i<n;i++)
        printf("\t%d ",arr[i]);
    return 0;
}