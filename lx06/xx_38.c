//用选择法对10个整数进行排序
#include<stdio.h>
int main(){
    int arr[10];
    int i,j,min_index,temp;

    //输入10个整数
    printf("请输入10个整数：\n");
    for(i=0;i<10;i++){
        scanf("%d",&arr[i]);
    }

    //选择排序
    for(i=0;i<9;i++){
        min_index = i;
        for(j=i+1;j<10;j++){
            if(arr[j]<arr[min_index]){
                min_index = j;
            }
        }
        //交换
        if(min_index != i){
            temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
        }
    }

    //输出排序后的数组
    printf("排序后的整数为：\n");
    for(i=0;i<10;i++){
        printf("%4d ",arr[i]);
    }
    printf("\n");

    return 0;
}