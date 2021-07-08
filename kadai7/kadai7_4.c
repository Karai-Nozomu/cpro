#include <stdio.h>
void swap(int *pa, int *pb){
    int temp = *pa;
    *pa = *pb;
    *pb = temp;
}

void minmax(int data[], int * min, int * max){
    int i;
    *min = data[0];
    *max = data[0];
    for (i = 1; i < 3; i++){
        if(*min > data[i]){
            swap(&*min, &data[i]);
        }
        if(*max < data[i]){
            swap(&*max, &data[i]);
        }
    }
}

int main(){
    int data[3];
    int min, max;
    int j;
    for (j = 0; j < 3; j++){
        printf("input %dst digit: ", j+1);
        scanf("%d", &data[j]);
    }
    minmax(data, &min, &max);
    printf("min: %d, max: %d", min, max);
    return 0;
}