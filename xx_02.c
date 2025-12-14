#include <stdio.h>

// 声明（可选，因为定义在 main 之后才需要；这里我们把定义放后面）

int main() {
    int a, b, c;
    int max(int x, int y);
    printf("请输入两个整数用逗号隔开\n");
    scanf("%d,%d", &a, &b);
    c = max(a, b);
    printf("max=%d\n", c);
    return 0;
}

// 👇 必须提供函数定义！
int max(int x,int y){

    int z;

    if(x>y){
        z = x;
    }
    else{
        z = y;
    }
    return(z);
}