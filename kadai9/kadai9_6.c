#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

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

void load(const char *filename, int m, int n, float *A, float *b) {
    FILE *fp = NULL;
    fp = fopen(filename, "r");
    if(!fp) {
    printf("File cannot open");
    return;
    }
    float temp;
    for (int i = 0; i < m * n; i++){
        fscanf(fp, "%f", &temp);
        A[i] = temp;
    }
    for (int i = 0; i < n; i++){
        fscanf(fp, "%f", &temp);
        b[i] = temp;
    }
    fclose(fp);
}


int main(int argc, char *argv[]){
    int n = 0, m = 0;
    if(argc > 1) m = atoi(argv[1]);
    if(argc > 2) n = atoi(argv[2]);
    float *A = malloc(sizeof(float) * n * m);
    float *b = malloc(sizeof(float) * n);
    load("test.dat", m, n, A, b);
    print(m, n, A);
    printf("\n");
    print(n, 1, b);
    return 0;
}
