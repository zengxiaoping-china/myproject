//将一个整数插入到一个“已排序”的数组中，保持其原有的排序规律（升序或降序）

#include<stdio.h>

int main(){
    int arr[100]; //✅ 安全：足够大，避免越界
    int i,j,temp;
    int num = 0;
    //输入10个整数
    printf("请输入10个整数：\n");
    for(i=0;i<10;i++){
        scanf("%d",&arr[i]);
    }
    //冒泡排序
    for(i=0;i<9;i++){
        for(j=0;j<9-i;j++){
            if(arr[j]>arr[j+1]){
                //交换
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    //输出排序后的数组
    printf("排序后的整数为：\n");
    for(i=0;i<10;i++){
        printf("%4d ",arr[i]);
    }
    printf("\n");

    //输入一个整数并将这个整数插入原来的数组中并按原来的排序规则输出
    printf("请输入一个整数：\n");
    scanf("%d",&num);

    // 插入排序

    // 新方法直接把 num 放到 arr[10]，然后对前11个做一次插入排序（更简单）
    // 从最后一个元素开始向前冒泡，直到位置正确
    arr[10] = num; // 将新数放在数组末尾
    for (i = 10; i > 0 && arr[i] < arr[i - 1]; i--) {
        // 交换 arr[i] 和 arr[i-1]
        temp = arr[i];
        arr[i] = arr[i - 1];
        arr[i - 1] = temp;
    }

    //原来的方法
    /*for(i=0;i<10;i++){
        if(arr[i]>num){
            //找到插入位置
            for(j=9;j>=i;j--){
                arr[j+1] = arr[j]; // 后移元素
            }
            arr[i] = num; // 插入新数
            break;
        }
    }
    // 如果新数最大，放在最后
    if(i == 10){
        arr[10] = num;
    }*/

    // 输出插入后的数组
    printf("插入后的排序整数为：\n");
    for(i=0;i<11;i++){
        printf("%4d ",arr[i]);
    }
    return 0;
}

//扩展：将一个整数插入到一个“已排序”的数组中，保持其原有的排序规律（升序或降序），并实现插入
/*
#include <stdio.h>

int main() {
    const int N = 10;
    int arr[11]; // 预留插入空间
    int i, j, num;

    // 输入10个整数
    printf("请输入10个已排序的整数（升序或降序）：\n");
    for (i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    // 判断排序方向
    int is_ascending = 1;
    int is_descending = 1;

    for (i = 0; i < N - 1; i++) {
        if (arr[i] > arr[i + 1]) is_ascending = 0;
        if (arr[i] < arr[i + 1]) is_descending = 0;
    }

    // 检查是否有效（至少有一种顺序成立）
    if (!is_ascending && !is_descending) {
        printf("错误：输入的数组不是升序也不是降序！\n");
        return 1;
    }

    // 输入要插入的整数
    printf("请输入要插入的整数：\n");
    scanf("%d", &num);

    // 找到插入位置
    int pos = N; // 默认插在最后
    if (is_ascending) {
        for (i = 0; i < N; i++) {
            if (num <= arr[i]) {
                pos = i;
                break;
            }
        }
    } else { // is_descending
        for (i = 0; i < N; i++) {
            if (num >= arr[i]) {
                pos = i;
                break;
            }
        }
    }

    // 将 pos 及之后的元素后移一位
    for (j = N; j > pos; j--) {
        arr[j] = arr[j - 1];
    }
    arr[pos] = num;

    // 输出结果
    printf("插入后的数组为：\n");
    for (i = 0; i < N + 1; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}*/