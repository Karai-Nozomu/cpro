#include<stdio.h>

void print_oct(int m, int n, const float * x, const char * name){
    printf("%s = [", name);
    int i;
    for (i = 0; i < m * n; i++){
        printf("%.4f", x[i]);
        printf(" ");
        if((i+1)%n==0){
            printf(";");
            printf("\n ");
        }
    }
    printf("];\n");
}

void scale(int n, float x, float * o){
    int i;
    for (i = 0; i < n; i++){
        o[i] *= x;
    }
}

int main(){
    float y[6] = {1, 1, 2, 3, 5, 8};
    print_oct(2, 3, y, "y");
    scale(6, 1.5, y);
    print_oct(2, 3, y, "y");
    return 0;
}