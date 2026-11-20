#include <stdio.h>

int main()
{
	int num1,num2,sum,times;
	printf("enter the first num:\n");
	scanf("%d",&num1);
	printf("enter the second num:\n");
	scanf("%d",&num2);
	sum=num1+num2;
	times=num1*num2;
	printf("the sum is %d\n",sum);
	printf("the times is %d\n",times);
	return 0;
}