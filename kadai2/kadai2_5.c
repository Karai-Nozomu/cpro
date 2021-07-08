#include <stdio.h>
int main(){
    int i ;
    int j;
    for (i = 0; i <10; i=i+1){
        for (j = i; j < 10;j = j + 1){
            printf("%d ", j);
        }
        printf("\n");
    }
    return 0;
}