#include <stdio.h>

float area(float r) {
    return 3.14 * r * r;
}

float volume(float h, float a) {
    return h * a;
}
int main() {
    float r, h, a, v;
    printf("Enter the radius of the circle: ");
    scanf("%f", &r);
    a = area(r);
    printf("The area of a circle with radius %f is %.4f\n\n", r, a);

    printf("Enter the height of the cylinder: ");
    scanf("%f", &h);
    v = volume(h, a);
    printf("The volume of a cylinder with radius %f and height %f is %f\n", r, h, v);
    return 0;
}
