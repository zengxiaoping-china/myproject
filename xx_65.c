//给出年、月、日,计算该日是该年的第几天。

#include<stdio.h>

int f1(int y);
int f2(int y,int m,int d);

int main(){
    int y,m,d,day_num;
    printf("\n请输入年、月、日：");
    scanf("%d %d %d",&y,&m,&d);
    if (m<=0 || m>12 || d>31 || d<=0 ||y<=0)
    {
        printf("错误：输入的日期错误!");
        return 0;
    }
    
    printf("\n您输入的日期是：%d年%d月%d日\n\n",y,m,d);
    day_num = f2(y,m,d);
    printf("%d年%d月%d日是该年的第%d天",y,m,d,day_num);
    return 0;
}

//判断是否是闰年的函数
int f1(int y){
    if (y % 4 == 0 && y % 100 !=0 || y % 400 == 0)
    {
        return 1;
    }
    return 0;
}

//求是该年的第几天的函数
int f2(int y,int m,int d){
    int i,j=1,k=1;
    int day_num1=0,day_num2=0,day_num3=0,day_sum=0;
    int yue_31[7]={1,3,5,7,8,10,12};
    int yue_30[4]={4,6,9,11};
    for (i = 1; i<m; i++)
    {
        if (i==yue_31[k-1])
        {
            day_num1=k*31;
            k++;
        }
        if (i==yue_30[j-1])
        {
            day_num2=j*30;
            j++;
        }
    }
    if (m>2 && f1(y))
    {
        day_num3=29;
    }
    else if (m>2)
    {
        day_num3=28;
    }
    day_sum=day_num1+day_num2+day_num3+d;
    return(day_sum);
}