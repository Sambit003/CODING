#include<stdio.h>
void main()
{
    char str[20],strcpy[20];
    int length=0,i,j,palc=0;
    printf("\n\tEnter a word : ");
    gets(str);
    for(i=0;str[i]!='\0';i++)
        length++;
    for(i=0,j=length-1;i<length,j>=0;i++,j--)
    {
        strcpy[j]=str[i];
    }
    strcpy[i]='\0';
    puts(strcpy);
    for(i=0;i<length;i++)
    {
        if(str[i]==strcpy[i])
            palc++;
    }
    if(palc==length)
        printf("\n\tPALINDROME");
    else
        printf("\n\tNOT PALINDROME");
}