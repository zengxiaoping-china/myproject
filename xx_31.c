//交换二维数组a和b的元素位置

#include<stdio.h>

int main(){
    int i,j,temp;
    //定义并初始化二维数组a和b
    int a[2][3] = {{1,2,3},{4,5,6}};
    int b[3][2] = {{1,4},{2,5},{3,6}};
    //交换a和b的元素位置
    for(i=0;i<2;i++){
        for(j=0;j<3;j++){
            temp = a[i][j];
            a[i][j] = b[j][i];
            b[j][i] = temp;
        }
    }
    //输出交换后的二维数组a和b
    printf("\nArray a after swapping:\n");
    for(i=0;i<2;i++){
        for(j=0;j<3;j++){
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    printf("Array b after swapping:\n");
    for(i=0;i<3;i++){
        for(j=0;j<2;j++){
            printf("%d ",b[i][j]);
        }
        printf("\n");
    }
    return 0;
}