#include <stdio.h>

int main()
{
	int grade;
	printf("enter your grades :\n");
	scanf("%d",&grade);
	if(grade>0)
	{
	if(grade>=0&&grade<50)
	{
		printf("failed");
	}
	else if(grade>=50&&grade<65)
	{
		printf("pass");
	}
	else if(grade>=65&&grade<75)
	{
		printf("good");
	}
	else if(grade>=75&&grade<85)
	{
		printf("very good");
	}
	else if(grade>=85&&grade<100)
	{
		printf("excellent");
	}
	}
	else
	{
		printf("enter valid number");
	}
	return 0;
}