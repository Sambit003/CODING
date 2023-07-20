#include <stdio.h>

int main(void) {
	int t,n,i;
	char s[6];
	scanf("%d",&t);
	while(t--)
	{
	    scanf("%d",&n);
	    for(i=0;i<n;i++)
	    {
	        if(s[i]=='A')
	            s[i]='T';
	        else if(s[i]=='T')
	            s[i]='A';
	        else if(s[i]=='C')
	            s[i]='G';
	        else if(s[i]=='G')
	            s[i]='C';
	    }
	    printf("%s",s);
	}
	return 0;
}