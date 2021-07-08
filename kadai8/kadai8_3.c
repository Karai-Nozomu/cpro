#include<stdio.h>
#include<math.h>
typedef struct{
    double x;
    double y;
}Vector2d;

void SclaeVector(Vector2d *vec, double s){
    vec->x *= s;
    vec->y *= s;
}


double GetLength(Vector2d *vec){
    return sqrt(pow(vec->x, 2.0) + pow(vec->y, 2.0));
}

int main(){
    double length, scale;
    Vector2d vec;
    printf("Input 2D Vector:");
    scanf("%lf%lf", &vec.x, &vec.y);
    printf("Input scale value: ");
    scanf("%lf", &scale);
    SclaeVector(&vec, scale);
    printf("Result: %.1f %.1f\n", vec.x, vec.y);
    length = GetLength(&vec);
    printf("Length: %.1f", length);
    return 0;
}