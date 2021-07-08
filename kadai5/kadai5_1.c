#include <stdio.h>
int fact(int n, int r) {
    if(r==0 || n==r){
        return  1;
    }
    if(r==1){
        return n;
    }
    return (fact(n - 1, r - 1) + fact(n - 1, r));
    }   
int main(void) {
    int n, r, ans;
    scanf("%d", &n);
    scanf("%d", &r);
    ans = fact(n, r);
    printf("%d", ans);
    return 0;
}
