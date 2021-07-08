#include <stdio.h>
int main(){
    int i;
    float a = 0, b = 0;
    double c = 0, d = 0;
    for (i = 1; i <= 1e+8; i++){
        a += 1e-8;
        c += 1e-8;
    }
    b = (1e-8) * (1e+8);
    d = (1e-8) * (1e+8);

    printf("%.20f\n%.20f\n%.20f\n%.20f\n", a, b, c, d);
    return 0;
}