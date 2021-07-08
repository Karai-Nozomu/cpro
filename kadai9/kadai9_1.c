#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void swap(float *pa, float *pb){
    float temp = *pa;
    *pa = *pb;
    *pb = temp;
}

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

void sort(float a[], int n){
    int i, j, flag = 1;
    for (i = n; flag; i--){
        flag = 0;
        for (j = 0; j < i-1; j++){
            if(a[j] > a[j+1]){
                swap(&a[j], &a[j + 1]);
                flag = 1;
            }
        }
    }
}

int main(int argc, char *argv[]){
    int n = 0;
    if( argc > 1 ){
        n = atoi(argv[1]);
    }
    float *y = malloc(sizeof(float) * n);
    rand_init(n, &*y);
    print(1, n, y);
    sort(y, n);
    print(1, n, y);
    return 0;
}
