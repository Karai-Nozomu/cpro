#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void swap(int *pa, int *pb){
    int temp = *pa;
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

void sort(float a[], float n){
    for (int i = 0; i < n - 1; i++){
        for (int j = n - 1; j > i; j--){
            if(a[j-1] > a[j]){
                float temp = a[j];
                a[j] = a[j - 1];
                a[j - 1] = temp;
            }
        }
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

void shuffle(int n, int index[]){
    int i, j;
    srand(time(NULL));
    for (int k = 0; k < n; k++){
        i = rand() % n;
        j = rand() % n;
        swap(&index[i], &index[j]);
    }
}

int main(int argc, char *argv[]){
    int n = 0;
    if( argc > 1 ){
        n = atoi(argv[1]);
    }
    float *y = malloc(sizeof(float) * n);
    rand_init(n, y);
    print(1, n, y);
    sort(y, n);
    print(1, n, y);
    int *index = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++){
        index[i] = i;
    }
    shuffle(n, index);
    for (int i = 0; i < n; i++){
        printf("%.4f ", y[index[i]]);
    }
    return 0;
}
