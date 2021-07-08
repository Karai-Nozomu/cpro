#include <stdio.h>
int main(){
    char input = 'a';
    printf("%c\n", input);
    printf("%d\n", input);
    printf("%x\n", input);

    input++;
    printf("%c\n", input);
    printf("%d\n", input);
    printf("%x\n", input);

    return 0;
}