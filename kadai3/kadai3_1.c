#include <math.h>
#include <stdio.h>
int main(){
    int i,n;
    int a = 1;
    scanf("%d", &n);
    for (i = 1; i < n + 1; i++){
        a *= i;
    }
    printf("%d", a);
    return 0;
}