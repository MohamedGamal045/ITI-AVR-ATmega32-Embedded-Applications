#include <stdio.h>
// gcc ASS2.c -o ASS2.exe
// ASS2.exe
int main()
{
    float num1, num2;
    char operations;
    printf("please enter the two number that you want to Calculate\n");
    printf("Enter the first number:");
    scanf("%f", &num1);
    printf("Enter the second number:");
    scanf("%f", &num2);    
    printf("please choose the operation ('+' , '-' , '/' , '*'):");
    scanf(" %c", &operations);
    switch (operations)
    {
        case '*': 
            printf("%f * %f = %f", num1, num2, num1 * num2);
            break;
        case '/':
            if (num2 != 0)
                printf("%f / %f = %f", num1, num2, num1 / num2);
            else
                printf("Error: Division by zero is not allowed.");
            break;

        case '+':
            printf("%f + %f = %f", num1, num2, num1 + num2);
            break;
        case '-':
            printf("%f - %f = %f", num1, num2, num1 - num2);
            break;
        default:
            printf("sorry, invalid operation");
    }
    return 0;
}
