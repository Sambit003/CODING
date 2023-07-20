#include<stdio.h>
int main()
{
    int arr[20],beg,end,mid,n,i,search;
    printf("\n\tEnter how many elements you want to insert: ");
    scanf("%d",&n);
    printf("\n\tEnter the elements (in sorted order): ");
    for(i=0;i<n;i++)
        scanf("%d",&arr[i]);
    beg=0;end=n-1;
    printf("\n\tEnter the element you want to search: ");
    scanf("%d",&search);
    if(arr[beg]<arr[end])  //ascending order search case
    {
        while(beg<=end)
        {
            mid=(beg+end)/2;
            if(arr[mid]==search)
            {
                printf("\n\tElement found");
                break;
            }
            if(search>arr[mid]) beg=mid+1;
            else end=mid-1;
        }
    }
    else if(arr[beg]>arr[end])  //desending order search case
    {
        while(beg<=end)
        {
            mid=(beg+end)/2;
            if(arr[mid]==search)
            {
                printf("\n\tElement found");
                break;
            }
            if(search<arr[mid]) beg=mid+1;
            else end=mid-1;
        }
    }
    if(beg>end) printf("\n\tElement not found");
    return 0;
}
