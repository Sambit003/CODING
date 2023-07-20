#include<stdio.h>
int main()
{
    int arr[20],i,n,bound,choice,pos,val,flag=0,j;
    printf("\n\tEnter the number of elements you want to input: ");
    scanf("%d",&n);
    printf("\n\tEnter the elements: ");
    for(i=0;i<n;i++)
        scanf("%d",&arr[i]);
    bound=n-1;
    printf("\n\n\t::Deletion::\n\t1. Delete by position\n\t2. Delete by value\n\n\tEnter your choice: ");
    scanf("%d",&choice);
    while(1)
    {
        switch(choice)
        {
            case 1:
                printf("\n\tEnter the position you want to delete: ");
                scanf("%d",&pos);
                if(pos-1>bound) printf("\n\tERROR");
                else
                {
                    for(i=pos-1;i<=bound;i++)
                        arr[i]=arr[i+1];
                    printf("\n\tDELETE SUCCESSFUL");
                    bound--;
                }
                break;
            case 2:
                printf("\n\tEnter the value you want to delete: ");
                scanf("%d",&val);
                for(i=0;i<=bound;i++)
                {
                    if(arr[i]==val)
                    {
                        for(j=i;j<=bound;j++)
                            arr[j]=arr[j+1];
                        printf("\n\tDELETE SUCCESSFUL");
                        break;
                    } 
                    else flag++;
                }
                if(flag!=0) printf("\n\tERROR");
                break;
            default: printf("\n\tWrong Choice:");
        }
    }
    return 0;
}