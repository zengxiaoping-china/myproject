//习题3.输入10 个整数,将其中最小的数与第一个数对换,把最大的数与最后一个数对换。写3个函数:(1)输入10个数;(2)进行处理;(3)输出10个数。


#include<stdio.h>

void num_scan(int *arr,int n);
void num_swap(int *arr,int n);
void num_print(int *arr,int n);

int main(){
    int array[10];
    int n=10;
    printf("\n请输入十个整数：");
    num_scan(array,n);
    num_swap(array,n);
    printf("\n输出交换后的十个整数：");
    num_print(array,n);
    printf("\n");
    return 0;
}

void num_scan(int *arr,int n){
    int i;
    for ( i = 0; i < n; i++)
    {
        scanf("%d",&arr[i]);
    }

}

void num_swap(int *arr, int n) {
    int min_index = 0;
    int max_index = 0;

    // 找最小值和最大值的索引（基于原始数组）
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[min_index]) {
            min_index = i;
        }
        if (arr[i] > arr[max_index]) {
            max_index = i;
        }
    }

    // 交换最小值到开头
    if (min_index != 0) {
        int temp = arr[0];
        arr[0] = arr[min_index];
        arr[min_index] = temp;
        
        // 如果最大值原本在位置 0，现在它被换到了 min_index
        if (max_index == 0) {
            max_index = min_index;
        }
    }

    // 交换最大值到最后
    if (max_index != n - 1) {
        int temp = arr[n - 1];
        arr[n - 1] = arr[max_index];
        arr[max_index] = temp;
    }
}

void num_print(int *arr,int n){
    int i;
    for ( i = 0; i < n; i++)
    {
        printf("%d ",arr[i]);
    }
}