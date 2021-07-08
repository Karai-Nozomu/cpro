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
    if( (b*b - 4*a*c)>=0 ){
    double answer1 = (-b + sqrt(b * b - 4*a * c)) / 2 * a;
    double answer2 = (-b - sqrt(b * b - 4*a * c)) / 2 * a;
    printf("%f\n%f", answer1, answer2);
    }else{
        double reanswer = -b / 2 * a;
        double imanswer = sqrt(4 * a * c - b * b) / 2 * a;
        printf("%f+i%f\n", reanswer, imanswer);
        printf("%f-i%f", reanswer, imanswer);
    }

    return 0;
}