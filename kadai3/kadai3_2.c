#include <math.h>
#include <stdio.h>
int main(){
    int n;
    int i = 1;
    int a = 1;
    scanf("%d", &n);
    while(i < n + 1){
        a *= i;
        i++;
    }
    printf("%d", a);
    return 0;
}