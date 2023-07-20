#include<stdio.h>
int main()
{
    int arr[20],i,n,srchval,flag=0;
    printf("\n\tEnter how many elements you want to insert (maximum 20): ");
    scanf("%d",&n);
    printf("\n\tEnter elements :");
    for(i=0;i<n;i++)
        scanf("%d",&arr[i]);
    printf("\n\tEnter the element you want to search for: ");
    scanf("%d",&srchval);
    for(i=0;i<n;i++)
    {
        if(srchval==arr[i])
        {
            printf("\n\tElement found at index %d",i+1);
            flag++;
            break;
        }
    }
    if(flag==0) printf("\n\tELEMENT NOT FOUND!\n");
    return 0;
}