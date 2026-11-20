#include <stdio.h>
// gcc ASS2.c -o ASS2.exe
// ASS2.exe
int main()
{
	int num;
		printf("Enter the number:");
		scanf("%d",&num);
	for(int i=1 ; i<=num ;i++)
	{
		printf("%d * %d = %d\n",num,i,num*i);
	}
    return 0;
}
