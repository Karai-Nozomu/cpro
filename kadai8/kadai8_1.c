#include<stdio.h>
#define NUMBER 5
void swap(int *pa, int *pb){
    int temp = *pa;
    *pa = *pb;
    *pb = temp;
}
/* 
void sort(int a[], int n){
    for (int i = 0; i < n - 1; i++){
        for (int j = n - 1; j > i; j--){
            if(a[j-1] > a[j]){
                int temp = a[j];
                a[j] = a[j - 1];
                a[j - 1] = temp;
            }
        }
        for (int k = 0; k < 6; k++){
            printf("%d ", a[k]);
        }
        printf("\n");
    }
}
*/

int main(){
    int data[6] = {64, 30, -8, 87, -45, 13};
    int i, j, k, flag = 1, loop = 1;
    for (i = 6; flag; i--){
        flag = 0;
        for (j = 0; j < i-1; j++){
            if(data[j] > data[j+1]){
                swap(&data[j], &data[j + 1]);
                flag = 1;
            }
        }
        printf("loop%d: ", loop);
        for (k = 0; k < 6; k++){
            printf("%d ", data[k]);
        }
        printf("\n");
        loop++;
    }
    /*sort(data, 6);*/
    return 0;
}