/*
输出以下4X5的矩阵。
    1   2   3   4   5
    2   4   6   8   10
    3   6   9   12  15
    4   8   12  16  20
*/
#include <stdio.h>
int main(){
    int i,j;
    printf("\n\t输出4X5的矩阵\n\n");
    for(i=1;i<=4;i++){
        for(j=1;j<=5;j++){
            //if(i==3 && j==1) break;
            printf("%4d",i*j);
        }
        printf("\n");
    }
    return 0;

}