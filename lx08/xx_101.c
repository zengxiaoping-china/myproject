//10.将一个5X5的矩阵中最大的元素放在中心,4个角分别放4个最小的元素(顺序为从左到右,从上到下依次从小到大存放),写一函数实现之。用 main 函数调用。

//保持原数组元素，进行元素交换

#include<stdio.h>
#include <stdlib.h>
#include <time.h>

void fun(int (*arr)[5],int rows,int cols);

int main(){
    // 设置随机种子（只需一次！）
    srand((unsigned int)time(NULL));
    int rows=5,cols=5;
    int array[5][5];
    int i,*p;
    p=&array[0][0];
    for ( i = 0; i < rows*cols; i++)
    {
        *p=i+1;
        //*p=rand() % 100;//随机数
        p++;
    }

    //输出交换前的二维数组
    p=array[0];
    for ( i = 0; i < rows*cols; i++)
    {
        printf("%2d ",*p);
        p++;
        if((i+1)%5==0) printf("\n");
    }

    fun(array,rows,cols);//交换元素

    printf("============================\n");//打印分割线

    //输出交换后的二维数组
    p=array[0];
    for ( i = 0; i < rows*cols; i++)
    {
        printf("%2d ",*p);
        p++;
        if((i+1)%5==0) printf("\n");
    }
    return 0;  
}

void fun(int (*arr)[5],int rows,int cols){
    int max_index=0,min1_index=0,min2_index=0,min3_index=0,min4_index=0;
    int i,j,k,temp;
    int *p,*p_temp;
    int arr_temp[5][5];
    p=&arr[0][0];
    p_temp=&arr_temp[0][0];
    
    //复制原二维数组到临时二维数组
    for ( i = 0; i < rows*cols; i++)
    {
        *p_temp++ = *p++;
    }
    
    p_temp=&arr_temp[0][0];//指针复位
    //对临时二维数组进行选择排序
    for ( i = 0; i < rows*cols-1; i++)
    {
        k=i;
        for ( j = i+1; j < rows*cols; j++)
        {
            if (*(p_temp+k)>*(p_temp+j))
            {
                k = j;
            }  
        }
        if (k!=i)
        {
            temp=*(p_temp+k);
            *(p_temp+k)=*(p_temp+i);
            *(p_temp+i)=temp;
        }      
    }

    p=&arr[0][0];//指针复位
    p_temp=&arr_temp[0][0];//指针复位
    //获取原数组元素下标
    for ( i = 0; i < rows*cols; i++)
    {
        if (*(p+i) == *(p_temp+0))
        {
            min1_index=i;
        }
    }
    //printf("min1_index = %d\n",min1_index);
    temp=*(p+0),*(p+0)=*(p+min1_index),*(p+min1_index)=temp;

    for ( i = 0; i < rows*cols; i++)
    {
        if (*(p+i) == *(p_temp+1))
        {
            min2_index=i;
        }
    }
    //printf("min2_index = %d\n",min2_index);
    temp=*(p+cols-1),*(p+cols-1)=*(p+min2_index),*(p+min2_index)=temp;

    for ( i = 0; i < rows*cols; i++)
    {
        if (*(p+i) == *(p_temp+2))
        {
            min3_index=i;
        }
    }
    //printf("min3_index = %d\n",min3_index);
    temp=*(p+(rows-1)*cols),*(p+(rows-1)*cols)=*(p+min3_index),*(p+min3_index)=temp;

    for ( i = 0; i < rows*cols; i++)
    {
        if (*(p+i) == *(p_temp+3))
        {
            min4_index=i;
        }
    }
    //printf("min4_index = %d\n",min4_index);
    temp=*(p+rows*cols-1),*(p+rows*cols-1)=*(p+min4_index),*(p+min4_index)=temp;

    for ( i = 0; i < rows*cols; i++)
    {
        if (*(p+i) == *(p_temp+rows*cols-1))
        {
            max_index=i;
        }
    }

    //printf("max_index = %d\n",max_index);

    //获取中心元素下标
    int center_row = rows / 2;   // 2
    int center_col = cols / 2;   // 2
    int offset = center_row * cols + center_col;  // 12

    //交换最大元素到中心
    temp=*(p+offset),*(p+offset)=*(p+max_index),*(p+max_index)=temp;       
}

        
        
        
        