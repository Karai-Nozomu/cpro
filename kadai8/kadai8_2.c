#include<stdio.h>
#include<math.h>

typedef struct{
    double x;
    double y;
}Vector2d;

double GetLength(Vector2d *vec){
    return sqrt(pow(vec->x, 2.0) + pow(vec->y, 2.0));
}

int main(){
    double length;
    Vector2d vec;
    printf("Input 2D Vector:");
    scanf("%lf%lf", &vec.x, &vec.y);
    length = GetLength(&vec);
    printf("Length: %.1f", length);
    return 0;
}