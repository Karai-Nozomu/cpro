#include <math.h>
#include <stdio.h>
int main()
{
    double a;
    double b;
    double c;
    printf("a = ");
    scanf("%lf", &a);
    printf("b = ");
    scanf("%lf", &b);
    printf("c = ");
    scanf("%lf", &c);
    double answer1 = (-b + sqrt(b * b - 4*a * c)) / 2 * a;
    double answer2 = (-b - sqrt(b * b - 4*a * c)) / 2 * a;
    printf("%f\n%f", answer1, answer2);


    return 0;
}