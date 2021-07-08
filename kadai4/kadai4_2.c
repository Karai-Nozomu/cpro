#include <stdio.h>
#define M 3
#define N 4
int main() {
    int a[M][N];
    int i, j;
    for(i=0; i<M; i++) {
        for(j=0; j<N; j++) {
            a[i][j] = 10 * i + j;
        }
    }
    for(i=0; i<M; i++) {
        for(j=0; j<N; j++) {
            if(j>0){
                printf(" ");
            }
            if(a[i][j]<10){
                printf(" ");
            }
            printf("%d", a[i][j]);
            }
            printf("\n");
        }
    return 0;
}
