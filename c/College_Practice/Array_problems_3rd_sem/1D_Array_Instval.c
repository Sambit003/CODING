#include<stdio.h>
int main()
{
    int arr[20],i,n,pos,bound,val;
    printf("Enter the number of elements you want to input: ");
    scanf("%d",&n);
    printf("\n\tEnter the elements: ");
    for(i=0;i<n;i++)
        scanf("%d",&arr[i]);
    bound=n-1;
    printf("\n\tEnter the position and value you want to insert: ");
    scanf("%d%d",&pos,&val);
    if(pos-1>bound)
    {
        if(pos-1>bound+1) printf("\n\tINSERTION ERROR");
        else
        {
            arr[pos-1]=val;
            printf("\n\tINSERTION SUCCESSFUL");
            bound++;
        }

    }
    else
    {
        for(i=bound;i>=pos-1;i--)
            arr[i+1]=arr[i];
        arr[pos-1]=val;
        printf("\n\tINSERTION SUCCESSFUL");
        bound++;
    }
    return 0;
}