#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void rand_init(int n, float * o){
    int i;
    srand(time(NULL));
    for (i = 0; i < n; i++){
        o[i] = (float)(2 * rand()) / RAND_MAX - 1;
    }
}

void print(int m, int n, const float * x) {
// 配列の要素を表示する例
    int i;
    for (i = 0; i < m * n; i++){
        printf("%.4f", x[i]);
        printf(" ");
        if((i+1)%n==0){
            printf("\n");
        }
    }
}

void relu(int n, const float *x, float *y){
    for (int i = 0; i < n; i++){
        if(x[i] > 0){
            y[i] = x[i];
        }
        else{
            y[i] = 0;
        }
    }
}

int main(int argc, char *argv[]){
    int n = 0;
    if( argc > 1 ) n = atoi(argv[1]);
    float *y = malloc(sizeof(float) * n);
    float *x = malloc(sizeof(float) * n);
    rand_init(n, x);
    print(1, n, x);
    relu(n, x, y);
    print(1, n, x);
    print(1, n, y);
    return 0;
}