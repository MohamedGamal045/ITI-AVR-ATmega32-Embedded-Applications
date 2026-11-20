#include <stdio.h>

int main() {
    int nums[10];
    for (int i = 0; i < 10; i++) {
        printf("Please enter number %d : ", i);
        scanf("%d", &nums[i]);
    }
    printf("\nNumbers in reverse order:\n");
    for (int i = 9; i >= 0; i--) {
        printf("%d\n", nums[i]);
    }
    return 0;
}
