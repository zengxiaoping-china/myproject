#include<stdio.h>
int main(){
    int c,s;
    double p,d,w,f;
    printf("请输入单价，重量和距离：");
    scanf("%lf,%lf,%d",&p,&w,&s);         //输入单价，重量和距离
    printf("单价：%10.2f元/吨\n",p);          //输出单价
    printf("重量：%10.2f吨\n",w);        //输出重量
    printf("距离：%10d公里\n",s);          //输出距离
    if (s>=3000) {
        c = 12;
    }
    else
    {
        c = s/250;
    }

    switch (c)
    {
    case 0:
        d = 0;
        break;
    case 1:
        d = 2;
        break;
    case 2:
    case 3:
        d = 5;
        break;
    case 4:
    case 5:
    case 6:
    case 7:
        d = 8;
        break;
    case 8:
    case 9:
    case 10:
    case 11:
        d = 10;
        break;
    case 12:
        d = 15;
    }
    printf("折扣率为：%10.2f%%\n",d);      //输出折扣率
    f = p*w*s*(1-d/100);                //计算运费
    printf("运费为：%10.2f元\n",f);      //输出运费
    return 0;
}