#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(){
    int plhand = 8;
    int cphand = 8;

    while(cphand==plhand){
    int plhand = 1;
    int cphand = 1;
    srand(time(NULL));
    while(cphand !=0 && cphand !=2 && cphand !=5){
        cphand = rand() % 6;
    }

    printf("Your input (0,2,5):");
    scanf("%d", &plhand);
    while(plhand !=0 && plhand !=2 && plhand !=5){
        puts("Invalid input => Input again.");
        printf("Your input (0,2,5):");
        scanf("%d", &plhand);
    }

    printf("Comp:%d vs You:%d => ", cphand, plhand);
    if (plhand==cphand){
        printf("Again.\n");
    }
    else if((plhand==5&&cphand==0)||(plhand==0&&cphand==2)||(plhand==2&&cphand==5)){
        printf("You win.");
        break;
    }
    else{
        printf("You lose.");
        break;
    }
    }    return 0;
}