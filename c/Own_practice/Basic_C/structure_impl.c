#include<stdio.h>
struct book{
  char name,author;
  int publish_date,price;
};
int main()
{
  int i;
  for(i=1;i<=3;i++)
  {
    printf("\n\tEnter the details of book %d : ",i);
    struct book i;
    scanf("%c",&i.name);fflush(stdin);scanf("%c",&i.author);
    scanf("%d%d",&i.publish_date,&i.price);
  }
  for(i=1;i<=3;i++)
  {
    printf("\n\tDetails of book %d :\n\tName : %c\n\tAuthor : %c\n\tPublishing Date : %d\n\tPrice : %d",i,i.name,i.author,i.publish_date,i.price);
  }
  return 0;
}
