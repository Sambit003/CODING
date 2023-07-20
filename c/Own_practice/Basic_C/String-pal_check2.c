#include<stdio.h>
void main()
{
    char str[20];
    int length=0,i,palch=0;
    printf("\n\tEnter the string :");
    gets(str);
    for(i=0;str[i]!='\0';i++)
        length++;
    for(i=0;i<length;i++)
    {
        if(str[i]!=str[length-1-i])
            palch++;
            break;
    }
    if(palch==0)
        printf("\n\tPALINDROME");
    else
        printf("\n\tNOT PALINDROME");
}