//练习二维数组作为函数参数使用

#include<stdio.h>

int main(){
    int max_value(int arr[][4]);
    void sort(int arr[][4]);
    int i,j,max;
    int arr[3][4] ={{23,29,63,45},{58,42,93,35},{36,48,78,25}};
    printf("\n======= 求下面这个3x4的二维数组中的最大数 =======\n\n");
    for ( i = 0; i < 3; i++)
    {
        for ( j = 0; j < 4; j++)
        {
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
    max = max_value(arr);
    printf("\n这个3x4的二维数组中的最大数是：%d\n\n",max);

    printf("======= 对这个3x4的二维数组中的元素进行排序 =======\n\n");
    sort(arr);
    return 0;
}

//求整形二维数组最大数值的函数
int max_value(int arr[][4]){
    int i,j,max,a,b;
    max = arr[0][0];
    for ( i = 0; i < 3; i++)
    {
        for ( j = 0; j < 4; j++)
        {
            if (max < arr[i][j])
            {
                max = arr[i][j];
                a = i,b = j;
            }
        }  
    }
    max = arr[a][b];
    return(max);
}

//对整形二维数组中的元素进行排序的函数
void sort(int arr[][4]){
    int a[12];
    int i,j,n = 0,c =0,k=0,temp;

    printf("先将二维数组转换成一维数组\n\n");
    for ( i = 0; i < 3; i++)
    {
        for ( j = 0; j < 4; j++)
        {
            a[n] = arr[i][j];
            n++;
        }
    }
    printf("转换后的一维数组是：");
    for ( i = 0; i < 12; i++)
    {
        printf("%d ",a[i]);
    }

    printf("\n\n对一维数组中的元素进行排序\n\n");
    
    //冒泡法排序
    /*
    for ( i = 0; i < 11; i++)
    {
        for ( j = 0; j < 11-i; j++)
        {
            if(a[j]>a[j+1]){
                temp = a[j],a[j] = a[j+1],a[j+1]=temp;
            }
        }  
    }
    */
    //选择法排序
    for ( i = 0; i < 11; i++)
    {
        k = i;
        for ( j =i+1; j < 12; j++)
        {
            if(a[j]<a[k]){
                k = j;
            }
        }
        if (k != i)
        {
            temp =a[i],a[i]=a[k],a[k]=temp;
        }
    }
    

    printf("排序后的一维数组是：");
    for ( i = 0; i < 12; i++)
    {
        printf("%d ",a[i]);
    }

    printf("\n\n将一维数组转换成原来的二维数组\n\n");
    for ( i = 0; i < 3; i++)
    {
        for ( j = 0; j < 4; j++)
        {
            arr[i][j] = a[c];
            c++;
        }
        
    }

    printf("转换后的二维数组是：\n\n");
    for ( i = 0; i < 3; i++)
    {
        for ( j = 0; j < 4; j++)
        {
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
}