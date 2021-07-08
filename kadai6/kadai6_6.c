#include<stdio.h>
#include<stdlib.h>
#include<time.h>

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

void rand_init(int n, float * o){
    int i;
    srand(time(NULL));
    for (i = 0; i < n; i++){
        o[i] = (float)(2 * rand()) / RAND_MAX - 1;
    }
}

int main(){
    float y[6];
    // 初期化前の値
    print_oct(2, 3, y, "y");
    rand_init(6, y);
    // 初期化後の値
    print_oct(2, 3, y, "y");
    return 0;

}