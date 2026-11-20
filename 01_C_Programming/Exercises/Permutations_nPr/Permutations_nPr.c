#include <stdio.h>
// gcc ASS1.c -o ASS1.exe
// ASS1.exe
	int factorial(int n) {
		int fact = 1;
		for (int i = n; i >= 1; i--) {
			fact *= i;
		}
		return fact;
	}
	int nPr(int n, int r) {
		return factorial(n) / factorial(n - r);
	}
	int main() {
		int num1, num2;
		printf("Enter two Number :\n");
		printf("Number1:");
		scanf("%d",&num1);
		printf("Number2:");
		scanf("%d",&num2);
		if(num1>=num2 && num1>=0&& num2>=0)
		{
		int show = nPr(num1, num2);
		printf("nPr: %d\n", show);
		}
		else
		{
			printf ("Invalid Number!");
		}
		return 0;
	}
