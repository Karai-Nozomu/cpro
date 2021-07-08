#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* 関数histを自分で作成 */
void hist(double tim){
    double cnt[10] = {0};
    int i = 0;
    int rnd;
    srand(time(NULL));
    while(i< tim){
        rnd = rand() % 10;
        cnt[rnd]++;
        i++;
    }
    printf("n=%7.0f:", tim);
    int j;
    double per;
    for (j = 0; j < 10;j++){
        per = (cnt[j] / tim) * 100;
        printf("%5.1f", per);
    }
    printf("\n");
}

int main() {
    hist(100);
    hist(1000);
    hist(10000);
    hist(100000);
    hist(1000000);
    return 0;
}
