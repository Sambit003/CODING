#include<stdio.h>
int main()
{
    int arr[20],i,n,esum=0,osum=0;
    printf("\n\tEnter how many elements you want to input: ");
    scanf("%d",&n);
    printf("\n\tEnter the elements: ");
    for(i=0;i<n;i++)
        scanf("%d",&arr[i]);
    printf("\n\tEven numbers: ");
    for(i=0;i<n;i++)
    {
        if(arr[i]%2==0)
        {
            printf("\t%d",arr[i]);
            esum+=arr[i];
        }
    }
    printf("\n\tOdd numbers: ");
    for(i=0;i<n;i++)
    {
        if(arr[i]%2!=0)
        {
            printf("\t%d",arr[i]);
            osum+=arr[i];
        }
    }
    printf("\n\tSum of even numbers: %d\n\tSum of odd numbers: %d",esum,osum);
    return 0;
}