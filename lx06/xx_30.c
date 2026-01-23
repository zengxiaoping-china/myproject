//任意输入10个整数，按从小到大的顺序排序，并输出排序过程，使用了冒泡法。

#include<stdio.h>

int main(){
    int i,j,temp;
    int f[10];
    printf("\nEnter 10 integers: ");
    for(i = 0; i < 10; i++){
        scanf("%d", &f[i]);
    }
    printf("\nSorting process:\n");
    for(j = 10; j > 1; j--){
        for(i = 1; i < j; i++){
            if(f[i - 1] > f[i]){
                temp = f[i - 1];
                f[i - 1] = f[i];
                f[i] = temp;
            }
        }
        for(i = 0; i < 10; i++){
        printf("%d ", f[i]);
        }
        printf("\n");
    }
    printf("\nSorted array: ");
    for(i = 0; i < 10; i++){
        printf("%d ", f[i]);
    }

    return 0;
}