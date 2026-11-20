#include <stdio.h>
// gcc ASS2.c -o ASS2.exe
// ASS2.exe
int factorial(int num) 
{
    int fact = 1;
    for (int i = num; i >= 1; i--) {
        fact *= i;
    }
    return fact;
}
int ncr(int n, int r) 
{
    return factorial(n)/ factorial(r) *factorial(n - r);
}
int main() 
{
	int num1, num2;
	printf("Enter two Number :\n");
	printf("Number1:");
	scanf("%d",&num1);
	printf("Number2:");
	scanf("%d",&num2);	
	if(num1>=num2 && num1>=0&& num2>=0)
	{
    int show = ncr(num1, num2);
    printf("ncr: %d\n", show);
	}
	else
	{
		printf ("Invalid Number!");
	}
    return 0;
}
