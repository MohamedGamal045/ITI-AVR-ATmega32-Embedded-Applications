// gcc ASS2.c -o ASS2.exe
// ASS2.exe
#include <stdio.h>
int main() 
{
    int n, i;
    int evenSum = 0, oddSum = 0;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    for(i = 0; i < n; i++) {
        printf("Enter element %d: ", i+1);
        scanf("%d", &arr[i]);
    }
    for(i = 0; i < n; i++) {
        if(arr[i] % 2 == 0) {
            printf("%d is even\n", arr[i]);
            evenSum += arr[i];
        } else {
            printf("%d is odd\n", arr[i]);
            oddSum += arr[i];
        }
    }
    printf("Sum of even numbers: %d\n", evenSum);
    printf("Sum of odd numbers: %d\n", oddSum);
    return 0;
}