#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
void init(int n, float x, float * o){
    int i;
    for (i = 0; i < n; i++){
        o[i] = x;
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

void save(const char *filename, int m, int n, const float *A, const float *b) {
    FILE *fp;
    fp = fopen(filename, "w");
    for (int i = 0; i < m * n; i++){
        fprintf(fp, "%.4f ", A[i]);
        if(i % n == n - 1){
            fprintf(fp, "\n");
        }
    }
    fprintf(fp, "\n");
    for (int i = 0; i < n; i++){
        fprintf(fp, "%.4f\n", b[i]);
    }
    fclose(fp);
}


int main(int argc, char *argv[]){
    int n = 0, m = 0;
    if(argc > 1) m = atoi(argv[1]);
    if(argc > 2) n = atoi(argv[2]);
    float *A = malloc(sizeof(float) * n * m);
    float *b = malloc(sizeof(float) * n);
    init(m * n, 1, A);
    init(n, 2, b);
    print(m, n, A);
    printf("\n");
    print(n, 1, b);
    save("test.dat", m, n, A, b);
    return 0;
}
