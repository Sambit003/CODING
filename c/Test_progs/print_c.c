#include<stdio.h>
#define print(x) { fprintf(stdout,"\n\t%d",x); }

int main(){
	int x;
	printf("\n\tEnter the number: ");
	fscanf(stdin,"%d",&x);
	print(x)
	return 0;
}
