#include <stdio.h>

int input(){
    int in;
    printf("n = ");
    scanf("%d", &in);
    return in;
}

void check(int in){
    int i;
    int ans[32];
    unsigned unin;
    unin = in;
    
    for (i = 0; i < 32; i++){
        ans[i] = unin>>i & 1;
    }
    printf("%d(10) = ", in);
    for (i = 31; i >= 0; i--){
        printf("%d", ans[i]);
    }
    printf(" (2)");
}

int main(){
    int in;
    in = input();
    check(in);
    return 0;
}