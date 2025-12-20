#include<stdio.h>

int main(){
    int i;
    int f[40] = {1, 1};
    for(i = 2; i < 40; i++){
        f[i] = f[i - 1] + f[i - 2];
    }
    for(i = 0; i < 40; i++){
        if(i % 10 == 0 && i != 0){
            printf("\n");
        }
        printf("%10d ", f[i]);
    }
    if(i % 10 != 0){
        printf("\n");
    }
}