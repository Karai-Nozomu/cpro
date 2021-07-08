#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

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

void softmax(int n, const float *x, float *y){
    float sigma = 0;
    float max_val = x[0];
    for(int i = 1; i < n; i++){
        if(x[i] > max_val) max_val = x[i];
    }
    for (int i = 0; i < n; i++){
        sigma += expf(x[i] - max_val);
    }
    for (int i = 0; i < n; i++){
        y[i] = (expf(x[i] - max_val)) / sigma;
    }
}

int main(int argc, char *argv[]){
    int n = 0;
    if( argc > 1 ) n = atoi(argv[1]);
    float *x = malloc(sizeof(float) * n);
    float *y = malloc(sizeof(float) * n);
    rand_init(n, x);
    print(1, n, x);
    softmax(n, x, y);
    print(1, n, x);
    print(1, n, y);
    return 0;
}