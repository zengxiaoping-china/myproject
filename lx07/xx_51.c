// 设计通用二维数组排序函数（升序，选择排序）

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 通用二维数组排序函数（升序，选择排序）
void sort_2d(int *arr, int rows, int cols) {
    int total = rows * cols;
    int *temp_arr = (int *)malloc(total * sizeof(int)); // 动态分配临时数组
    if (!temp_arr) {
        printf("内存分配失败！\n");
        return;
    }

    // 1. 将二维数组复制到一维临时数组
    for (int i = 0; i < total; i++) {
        temp_arr[i] = arr[i];
    }

    printf("转换后的一维数组是：\n\narray { ");
    for (int i = 0; i < total; i++) {
        printf("%4d ", temp_arr[i]);
        if((i+1) % 30 == 0) printf("\n\n        ");
    }
    printf("}\n\n");

    // 2. 对一维数组进行选择排序
    for (int i = 0; i < total - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < total; j++) {
            if (temp_arr[j] < temp_arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int temp = temp_arr[i];
            temp_arr[i] = temp_arr[min_idx];
            temp_arr[min_idx] = temp;
        }
    }

    printf("排序后的一维数组是：\n\narray { ");
    for (int i = 0; i < total; i++) {
        printf("%4d ", temp_arr[i]);
        if((i+1) % 30 == 0) printf("\n\n        ");
    }
    printf("}\n\n");

    // 3. 将排序结果写回原二维数组
    for (int i = 0; i < total; i++) {
        arr[i] = temp_arr[i];
    }

    free(temp_arr); // 释放临时内存

    // 4. 打印排序后的二维数组
    printf("转换后的二维数组是：\n\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d ", arr[i * cols + j]); // 按行优先访问
        }
        printf("\n\n");
    }
}

int main() {
    int rows = 8, cols = 8;
    srand((unsigned int)time(NULL));
    int *data = (int *)malloc(rows * cols * sizeof(int));
    
    // 初始化数据（按行优先）
    int val = 1;
    for (int i = 0; i < rows * cols; i++) {
        data[i] = rand() % 100;  // 随机数范围：0 ~ 99
    }

    sort_2d(data, rows, cols);

    free(data);
    return 0;
}