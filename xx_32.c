//给定一个3X4的二维数组，编写一个程序，查找并输出该数组中的最大值及其所在的位置（行号和列号）。

#include<stdio.h>

int main(){
    int i,j,temp,max;
    int row,col;
    //定义并初始化二维数组a
    int a[3][4] = {{36,24,63,39},{56,76,27,81},{63,18,61,22}};
    int b[12];
    printf("\n这个3X4的数组元素为：\n\n");
    //输出二维数组a的元素
    for(i=0;i<3;i++){
        for(j=0;j<4;j++){          
            printf("%4d ",a[i][j]);
        }
        printf("\n");
    }
    /*
    //查找并输出二维数组a中的最大值及其位置
    temp = a[0][0]; //初始化最大值
    for(i=0;i<3;i++){
        for(j=0;j<4;j++){          
            if(a[i][j]>temp){
                temp=a[i][j];
                row=i;
                col=j;
            }
        }
    }
    //输出最大值及其位置
    printf("\n这个3X4的数组中最大的数字是： %d , 它在第 %d 行, 第 %d 列\n\n",temp,row+1,col+1);

    //对这个3X4的数组元素每行进行排序
    max = a[0][0]; //初始化最大值
    for(i=0;i<3;i++){
        for(int c=0;c<3;c++){
            for(j=1;j<4-c;j++){          
                if(a[i][j]<a[i][j-1]){
                    temp=a[i][j];
                    a[i][j]=a[i][j-1];
                    a[i][j-1]=temp;
                }
            }
        }
    }
    */
   
    //将二维数组a的元素存入一维数组b
    int n = 0;
        for(i=0;i<3;i++){
            for(j=0;j<4;j++){          
                b[n]=a[i][j];
                n++;
            }
        }
    
    //输出一维数组b的元素
    printf("\n将二维数组a的元素存入一维数组b：\n\n");
    for(i=0;i<12;i++){
        printf("%4d ",b[i]);
    }
    printf("\n");

    //使用冒泡法对一维数组b进行排序
    for(int m=12;m>1;m--){
        for(int n=1;n<m;n++){
            if(b[n-1]>b[n]){
                temp=b[n-1];
                b[n-1]=b[n];
                b[n]=temp;
            }
        }
    }
    //将排序后的一维数组b的元素重新赋值给二维数组a
    int c = 0;
        for(i=0;i<3;i++){
            for(j=0;j<4;j++){          
                a[i][j]=b[c];
                c++;
            }
        }
    //输出排序后的二维数组a的元素
    printf("\n这个3X4的数组元素排序后为：\n\n");
    for(i=0;i<3;i++){
        for(j=0;j<4;j++){          
            printf("%4d ",a[i][j]);
        }
        printf("\n");
    }
    return 0;
}