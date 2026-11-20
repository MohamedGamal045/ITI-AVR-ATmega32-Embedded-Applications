#include <stdio.h>
// gcc ASS1.c -o ASS1.exe
// ASS1.exe
int main() 
{
    int n, i, j, temp;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
	
	int arr[n];
    for(i = 0; i < n; i++) {
        printf("Enter element %d: ", i+1);
        scanf("%d", &arr[i]);
    }

    for(i = 0; i < n-1; i++) {
        for(j = 0; j < n-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    printf("Minimum value: %d\n", arr[0]);
    printf("Maximum value: %d\n", arr[n-1]);
    return 0;
}