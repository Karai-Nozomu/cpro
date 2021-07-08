#include<stdio.h>
int main(){
    FILE *fp = NULL;
    FILE *fp1;
    fp1 = fopen("test.bak", "w");
    char str[128];
    fp = fopen("test.txt", "r");
    if(!fp) {
    printf("File cannot open");
    return 0;
    }
    while ( fgets(str, 128, fp) ){
    printf("%s", str);
    fprintf(fp1, "%s", str);
    }
    printf("End");
    fclose(fp);
    fclose(fp1);
}
