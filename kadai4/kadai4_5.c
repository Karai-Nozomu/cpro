#include <stdio.h>

int input(){
    int in;
    printf("n = ");
    scanf("%d", &in);
    while(in<0){
        puts("Invalid input\n");
        printf("n = ");
        scanf("%d", &in);
    }
    return in;
}

int fact(int in){
    int ans=1,i;
    if(in==0){
        ans = 1;
    }
    else{
        for (i = 1; i < in + 1;i++){
            ans *= i;
        }
    }
    return ans;
}

int perm(int n,int r){
    int ans,bunsi,bunbo;
    bunsi = fact(n);
    bunbo = fact(n - r);
    ans = bunsi / bunbo;
    return ans;
}

int main(){
    int n,i,ans;
    n = input();
    for (i = 0; i < n + 1;i++){
        ans = perm(n, i);
        printf("perm(%d,%d) = %d\n", n, i, ans);
    }
    return 0;
}