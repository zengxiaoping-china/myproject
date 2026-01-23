//10.将一个5X5的矩阵中最大的元素放在中心,4个角分别放4个最小的元素(顺序为从左到右,从上到下依次从小到大存放),写一函数实现之。用 main 函数调用。

//直接赋值 不搞交换

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fun(int (*arr)[5], int rows, int cols);

int main() {
    srand((unsigned int)time(NULL));
    int rows = 5, cols = 5;
    int array[5][5];
    int *p = &array[0][0];

    // 初始化数组（可用随机数或连续数）
    for (int i = 0; i < rows * cols; i++) {
        *p = rand() % 100 + 1;   // 随机数（1~100）
        // *p = i + 1;           // 连续数（1~25），便于测试
        p++;
    }

    // 输出原始矩阵
    printf("原始矩阵:\n");
    p = &array[0][0];
    for (int i = 0; i < rows * cols; i++) {
        printf("%2d ", *p++);
        if ((i + 1) % cols == 0) printf("\n");
    }

    fun(array, rows, cols); // 处理

    printf("============================\n");

    // 输出处理后矩阵
    printf("处理后矩阵:\n");
    p = &array[0][0];
    for (int i = 0; i < rows * cols; i++) {
        printf("%2d ", *p++);
        if ((i + 1) % cols == 0) printf("\n");
    }

    return 0;
}

// 核心函数：排序找值，直接赋值
void fun(int (*arr)[5], int rows, int cols) {
    int *p = &arr[0][0];
    int n = rows * cols;
    int temp[25]; // 用于排序的副本

    // 1. 复制原数组
    for (int i = 0; i < n; i++) {
        temp[i] = p[i];
    }

    // 2. 对副本进行升序排序（选择排序，也可用 qsort）
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (temp[j] < temp[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int t = temp[i];
            temp[i] = temp[min_idx];
            temp[min_idx] = t;
        }
    }

    // 3. 直接赋值到目标位置（排序后：前4个最小，最后一个最大）
    p[0]                     = temp[0];   // 左上角 [0][0]
    p[cols - 1]              = temp[1];   // 右上角 [0][4]
    p[(rows - 1) * cols]     = temp[2];   // 左下角 [4][0]
    p[rows * cols - 1]       = temp[3];   // 右下角 [4][4]
    p[(rows / 2) * cols + (cols / 2)] = temp[n - 1]; // 中心 [2][2]
}