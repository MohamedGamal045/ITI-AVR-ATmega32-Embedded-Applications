#include <stdio.h>

int main()
{
	int age;
	printf("enter your age :\n");
	scanf("%d",&age);
	if(age>=18)
	{
		printf("your age is %d so, you can drive",age);
	}
	else
	{
		printf("you can not drive");
	}

	return 0;
}