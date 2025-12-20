//输出一个10行的杨辉三角

#include<stdio.h>

int main(){
    int n = 10;
    int num[10][10] = {0};
    int i,j,k;
    
    //计算杨辉三角
    for(i=0;i<n;i++){
        num[i][0] = 1;
        num[i][i] = 1;
        for(j=1;j<i;j++){
            num[i][j] = num[i-1][j-1] + num[i-1][j];
        }
    }

    //输出杨辉三角
    printf("\n输出一个%d行杨辉三角\n\n", n);
    for(i=0;i<n;i++){
        for(j=0;j<=i;j++){
            printf("%4d ",num[i][j]);
        }
        printf("\n");
    }

    //输出美化后的杨辉三角
    printf("\n\n输出一个美化后的%d行杨辉三角\n\n", n);
    for(i=0;i<n;i++){
        for(k=0;k<n-i-1;k++){
            printf("  ");
        }
        for(j=0;j<=i;j++){
            printf("%4d ",num[i][j]);
        }
        printf("\n");
    }

    return 0;
}