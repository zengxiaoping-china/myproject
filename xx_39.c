//求一个3x3的整形矩阵的主对角线和副对角线之和（中心元素没有去重）

#include<stdio.h>

int main(){
    int arr[3][3];
    int i,j,sum,sum1,sum2;
    //输入3x3矩阵
    printf("请输入一个3x3矩阵：\n");
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            scanf("%d",&arr[i][j]);
        }
    }
    //输出矩阵
    printf("输出矩阵：\n");
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            printf("%4d ",arr[i][j]);
        }
        printf("\n");
    }
    //计算主对角线和副对角线之和
    printf("计算主对角线和副对角线之和：\n");
    sum1 = 0;
    sum2 = 0;
    for(i=0;i<3;i++){
        sum1 += arr[i][i];         // 主对角线
        sum2 += arr[i][2 - i];     // 副对角线
    }
    sum = sum1 + sum2;
    printf("对角线之和为：%d\n", sum);
    printf("主对角线之和为：%d\n", sum1);
    printf("副对角线之和为：%d\n", sum2);
}


//扩展：求一个n x n的整形矩阵的主对角线和副对角线之和，要求去掉重复元素（当n为奇数时，中心元素重复计算了一次）

/*
#include <stdio.h>

int main() {
    int n;
    printf("请输入矩阵阶数 n: ");
    scanf("%d", &n);

    int matrix[100][100];

    printf("请按行输入 %d x %d 的矩阵（每行 %d 个整数，空格隔开）:\n", n, n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);  // 自动处理空格和换行
        }
    }

    // 计算对角线之和（去重）
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += matrix[i][i];
        sum += matrix[i][n - 1 - i];
    }
    if (n % 2 == 1) {
        sum -= matrix[n/2][n/2];  // 去掉中心重复
    }

    printf("对角线元素之和（去重）为: %d\n", sum);
    return 0;
}
*/