//习题 1.输入 n 个整数,按由小到大的顺序输出。

#include<stdio.h>

void selection_sort(int array[],int n);

void bubble_sort(int *array,int n);

int main(){
    int arr[50];
    int *p,i,n=5;
    p=arr;
    printf("\n请输入%d个整数：",n);
    for (i = 0; i < n; i++)
    {
        scanf("%d",p+i);
    }

    //selection_sort(p,n);

    bubble_sort(p,n);

    printf("\n将%d个整数由小到大的顺序输出:",n);
    for ( i = 0; i < n; i++)
    {
        printf("%d ",*(p+i));
    }
}
//选择法排序
void selection_sort(int array[],int n){
    int temp,i,j,k;
    for ( i = 0; i < n-1; i++)
    {
        k=i;
        for ( j = i+1; j< n; j++)
        {
            if (array[k]>array[j])
            {
                k=j;
            }
            if (k!=i)
            {
                temp=array[k],array[k]=array[i],array[i]=temp;
            }   
        }
        
    } 
}

//冒泡法排序
void bubble_sort(int *array,int n){
    int temp,i,j;
    for ( i = 0; i < n-2; i++)
    {
        for ( j = 0; j < n-1-i; j++)
        {
           if (*(array+j)>*(array+j+1))
           {
            temp=*(array+j),*(array+j)=*(array+j+1),*(array+j+1)=temp;
           }
        }  
    }   
}