#include <stdio.h>
// gcc ASS1.c -o ASS1.exe
// ASS1.exe
int main()
{
	int num1, num2, num3;
	printf("please enter the three number:\n");
	printf("Enter the first number:");
	scanf("%d",&num1);
	printf("Enter the second number:");
	scanf("%d",&num2);
	printf("Enter the thered number:");
	scanf("%d",&num3);
	
	if (num1 > num2 && num1 > num3 )
	{
		printf(" The greatest number is:%d",num1);
	}
	else if (num2 > num1 && num2 > num3 )
	{
		printf(" The greatest number is:%d",num2);
	}
	else
	{
		printf(" The greatest number is:%d",num3);
	}
	return 0;
}