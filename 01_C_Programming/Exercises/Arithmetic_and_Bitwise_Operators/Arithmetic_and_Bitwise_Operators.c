#include <stdio.h>

int main()
{
	int a,b,add,sub,AND,OR,XOR;
	printf("Please Enter number a: ");
	scanf("%d",&a);
	printf("Please Enter number b: ");
	scanf("%d",&b);
	add=a+b;
	sub=a-b;
	AND=a&b;
	OR=a|b;
	XOR=a^b;
	printf("a + b = %d\n",add);
	printf("a - b = %d\n",sub);
	printf("a & b = %d\n",AND);
	printf("a | b = %d\n",OR);
	printf("a ^ b = %d\n",XOR);
return 0;	
}
