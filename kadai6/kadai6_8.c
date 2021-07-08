#include<stdio.h>

void print_oct(int m, int n, const float * x, const char * name){
    printf("%s = [", name);
    int i;
    for (i = 0; i < m * n; i++){
        printf("%.4f", x[i]);
        printf(" ");
        if(i%n==n-1){
            printf(";");
            printf("\n ");
        }
    }
    printf("];\n");
}

void mul(int m, int n, const float * x, const float * A, float * o){
    int i,low,line;
    for (i = 0; i < m * n; i++){
        low = i / n;
        line = i % n;
        o[low] += A[i] * x[line];
    }
}

void add(int n, const float * x, float * o){
    int i;
    for (i = 0; i < n; i++){
        o[i] += x[i];
    }
}

void fc(int m, int n, const float * x, const float * A, const float * b, float * o){
    mul(m, n, x, A, o);
    add(m, b, o);
}

int main(){
    float A[6] = {1,2,3,4,5,6};
    float b[2] = {0.5, 0.25};
    float x[3] = {2,3,5};
    float o[2] = {0};
    fc(2, 3, x, A, b, o);
    print_oct(2, 3, A, "A");
    print_oct(2, 1, b, "b");
    print_oct(3, 1, x, "x");
    print_oct(2, 1, o, "o");
    return 0;

}