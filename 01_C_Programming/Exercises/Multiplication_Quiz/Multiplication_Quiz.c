#include <stdio.h>
// gcc ASS1.c -o ASS1.exe
// ASS1.exe
int main()
{
	int number;
	do{
		printf("enter the result of equation:\n 5*9 =");
		scanf("%d",&number);
	}while(number!=45);
	printf("You finally woke up!");
    return 0;
}
