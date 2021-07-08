#include <stdio.h>
int main()
{
    int len = 0;
    char str[128];
    printf("input a word: ");
    scanf("%s", str);
    while(str[len]){
        if(str[len] == 'z'){
            str[len] = 'a';
            len++;
        }
        if(str[len] == 'Z'){
            str[len] = 'A';
            len++;
        }
        else{
            str[len] += 1;
            len++;
        }
    }   
    printf("%s\n", str);
    return 0;
}

