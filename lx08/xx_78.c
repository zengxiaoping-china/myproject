//使用指针变量对10个整数进行排序（从大到小）

#include<stdio.h>

void sort(int *x,int n);

void sort_new(int *x,int n);

void selection_sort(int x[],int n);

int main(){
    int array[10]={77,36,18,54,97,69,89,48,85,41};
    int i,n=10;
    printf("\n整数排序前\n");
    for ( i = 0; i < n; i++)
    {
        printf("%d ",array[i]);
    }
    printf("\n=============================\n");

    sort(array,n);

    printf("冒泡法排序后\n");
    for ( i = 0; i < n; i++)
    {
        printf("%d ",array[i]);
    }

    printf("\n=============================\n");

    sort_new(array,n);

    printf("纯指针冒泡法排序后\n");
    for ( i = 0; i < n; i++)
    {
        printf("%d ",array[i]);
    }

    printf("\n=============================\n");

    selection_sort(array,n);

    printf("选择法排序后\n");
    for ( i = 0; i < n; i++)
    {
        printf("%d ",array[i]);
    }
    printf("\n");
    return 0;
}

//对整形数组进行冒泡法排序函数
void sort(int *x,int n){
    int i,j,temp;
    for ( i = 0; i < n-1; i++)
    {
        for ( j = 0; j < n-1-i; j++)
       {
            if (*(x+j)>*(x+j+1))
            {
                temp =*(x+j);
                *(x+j)= *(x+j+1);
                *(x+j+1) = temp;
            }     
       } 
    }   
}
//纯指针对整形数组进行冒泡法排序函数
void sort_new(int *x, int n) {
    int *end = x + n;          // 指向数组末尾之后（x[n] 的位置）
    int *last;                 // 指向当前未排序部分的最后一个元素

    // 外层：每轮确定一个最大值放到末尾
    for (last = end - 1; last > x; last--) {
        int *p;
        int swapped = 0; //设置优化变量
        // 内层：从开头扫描到 last - 1（因为要比较 p 和 p+1）
        for (p = x; p < last; p++) {
            if (*p > *(p + 1)) {
                int temp = *p;
                *p = *(p + 1);
                *(p + 1) = temp;
                swapped = 1;
            }
        }
        if (!swapped) break; // 已有序，提前退出
    }
}

//对整形数组进行选择法排序函数
void selection_sort(int x[],int n){
    int i,j,k,temp;
    for ( i = 0; i < n-1; i++)
    {
        k=i;
        for ( j = i+1; j < n; j++)
        {
            if (x[k]>x[j])
            {
                k = j;
            }  
            if (k!=i)
            {
                temp = x[k],x[k]=x[i],x[i]=temp;
            }      
        } 
    }  
}