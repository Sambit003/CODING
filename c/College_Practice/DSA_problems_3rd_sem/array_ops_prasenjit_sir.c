#include<stdio.h>
#include<stdlib.h>

#define size 5           // maximum allocated size for the data structure

struct List
{
    int arr[size+1];
    int max;                // maximum occupied size with the data
};

struct List create(struct List x)
{
    int i,n;

    printf("\n enter how many element you want to insert initially ::");
    scanf("%d",&n);
    if(n>0)
    {
    for(i=0;i<n;i++)
    {
        printf("\n enter the data :");
        scanf("%d",&x.arr[i]);
    }
    x.max=n;
    }

    return x;
}


struct List insert(struct List x)
{
    int val,pos;
    printf("\n\n\tEnter the position where you want to insert: ");
    scanf("%d",&pos);
    printf("\n\n\tEnter the value that you want to insert: ");
    scanf("%d",&val);

    if(pos-1 >=0 && pos-1 <= x.max)
    {
        for(int i=x.max;i>=pos-1;i--)
            x.arr[i+1]=x.arr[i];

        x.arr[pos-1]=val;

        x.max++;
        printf("\n\t Insertion successful");
    }
    else
        printf("\n\tERROR IN POSITION\nInsertion not possible");

    return x;
}



struct List del(struct List x)
{
    int pos;
    printf("\n\n\tEnter the position you want to delete: ");
    scanf("%d",&pos);
    if(pos-1>=0 && pos-1 < x.max)
    {
        for(int i=pos-1;i<=x.max;i++)
            x.arr[i]=x.arr[i+1];

        x.max--;
        printf("\n ONE ELEMENT DELETED SUCCESSFULLY");
    }
    else
    printf("\n\tERROR IN POSITION");

    return x;
}


void display(struct List x)
{
    printf("\n\n\tFINAL ARRAY (%d Elements):",x.max);
    for(int i=0;i<x.max;i++)
        printf("\t%d",x.arr[i]);
}



int main()
{
    struct List l;
    int i,choice;
    l.max=0;

     l=create(l);


        while(1)
        {
            system("cls");
            display(l);
            printf("\n\n\t::OPTION::\n\n\t1. Insert\n\t2. Delete\n\t3. Display Final Array\n\tAny key to Exit\n\n\tEnter choice: ");
            scanf("%d",&choice);

            switch(choice)
            {
                case 1:
                    if(l.max < size)
                        l=insert(l);
                    else
                        printf("\n\tMAX LIMIT OF SPACE REACHED :(");
                    break;
                case 2:
                    if(l.max > 0)
                        l=del(l);
                    else
                        printf("\n\tNo DATA PRESENT :(");
                    break;
                case 3:
                    if(l.max > 0)
                        display(l);
                    else
                        printf("\n\tNo DATA PRESENT :(");
                    break;
                default:
                    exit(1);

            }
            printf("\n");
            system("pause");
        }
    }


