#include <stdio.h>
int main() {
    float x = 1,ans;
    int i;
    for(i=0 ; i<10 ; i++) {
        ans = x - (1.0 / 3.0) * (i + 1);
        if(ans == 0) {
            break;
        }
        printf("%.20f\n", ans);
    }
    return 0;
}
