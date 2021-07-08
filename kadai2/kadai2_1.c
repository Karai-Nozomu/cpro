#include <stdio.h>
int main()
{
int x;
printf("Type an integer: \n");
scanf("%d", &x);

if( x%3 == 0 || x%5 == 0 ){
    puts("YES");
}
else{
    puts("NO");
}

return 0;
}