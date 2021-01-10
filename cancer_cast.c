#include <stdio.h>
#include <stdlib.h>

int main(){
    srand(2020);
    for(int i=0; i < 10; ++i) {
        int res = rand();
        printf("%x %d\n", res, res);
        printf("%x %d\n", (char) res, (char) res);
        printf("%x\n", (char) (res % 5+'a'));
        printf("%c\n", (char) (res % 5+'a'));
        printf("%x\n", (res % 5+'a'));
        printf("%c\n", (res % 5+'a'));
        printf("-------------\n");
    }
}